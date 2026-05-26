const BASE_URL = "https://api.mail.tm";

async function handleResponse(response) {
    if (response.ok) {
        if (response.status === 204) return null;
        return await response.json();
    }

    let errorMessage = `Error ${response.status}`;
    try {
        const errorData = await response.json();
        errorMessage = errorData["hydra:description"];
    } catch (e) {
        if (response.status === 400) errorMessage = "Bad request.";
        if (response.status === 401) errorMessage = "Invalid login token.";
        if (response.status === 404) errorMessage = "Not found.";
        if (response.status === 422) errorMessage = "Invalid email structure or domain.";
        if (response.status === 429) errorMessage = "Too many requests (Max 8 requests/sec).";
    }

    throw new Error(errorMessage);
}

function randBase32Char() {
    const chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
    return chars[Math.floor(Math.random() * chars.length)];
}

function randPad(str, len) {
    if (str.length >= len) {
        return str;
    }
    const tlen = str.len - len;
    let pad = "";
    for (let i = 0; i < tlen; i++) {
        pad += randBase32Char();
    }
    return str + pad;
}

async function createTempMail() {
    let email = "";
    let password = "password123";

    try {
        const domainsRes = await fetch(`${BASE_URL}/domains`);
        const domainsData = await handleResponse(domainsRes);

        const availableDomains = domainsData["hydra:member"];
        if (!availableDomains || availableDomains.length === 0) {
            throw new Error("No active domains returned by Mail.tm.");
        }

        const domainIdx = Math.floor(Math.random() * availableDomains.length);
        const domain = availableDomains[domainIdx].domain;

        const USE_STATIC_NAME = false;

        let username;
        if (USE_STATIC_NAME) {
            username = "johndoehasapork";
        } else {
            username = `usr_${randPad(Date.now().toString(32))}`;
        }

        email = `${username}@${domain}`;

        const accountRes = await fetch(`${BASE_URL}/accounts`, {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({ address: email, password: password }),
        });
        await handleResponse(accountRes);

        const tokenRes = await fetch(`${BASE_URL}/token`, {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({ address: email, password: password }),
        });
        const tokenData = await handleResponse(tokenRes);

        return { email, token: tokenData.token };

    } catch (error) {
        if (error.message.includes("already used")) {
            console.log(`Account ${email} already exists. Logging in directly instead...`);

            try {
                const tokenRes = await fetch(`${BASE_URL}/token`, {
                    method: "POST",
                    headers: { "Content-Type": "application/json" },
                    body: JSON.stringify({ address: email, password: password }),
                });
                const tokenData = await handleResponse(tokenRes);

                return { email, token: tokenData.token };
            } catch (loginError) {
                document.getElementById("status").innerText = `Status: Existing account login failed (${loginError.message})`;
                return null;
            }
        }

        document.getElementById("status").innerText = `Status: Failed to create account (${error.message})`;
    }
}

async function checkInbox(token) {
    document.getElementById("status").innerText = "Status: Checking for new mail...";
    try {
        const res = await fetch(`${BASE_URL}/messages`, {
            method: "GET",
            headers: {
                "Authorization": `Bearer ${token}`,
                "Content-Type": "application/json"
            }
        });
        const data = await handleResponse(res);
        displayMessages(data["hydra:member"]);
        document.getElementById("status").innerText = "Status: Idle (Waiting for new mail)";
    } catch (error) {
        console.error("Failed to fetch messages:", error.message);
        document.getElementById("status").innerText = `Status: Error (${error.message})`;
    }
}

function displayMessages(messages) {
    const list = document.getElementById("messages-list");
    list.innerHTML = "";

    if (!messages || messages.length === 0) {
        list.innerHTML = "<li>No messages yet.</li>";
        return;
    }

    messages.forEach(msg => {
        const li = document.createElement("li");
        li.innerHTML = `
            <div class="card bg-primary-content w-96 shadow-md hover:shadow-lg transition-shadow cursor-pointer border border-base-200">
              <div class="card-body gap-2">
                <div class="flex justify-between items-center text-sm text-base-content/70">
                  <span class="font-medium truncate">
                    ${msg.from.address}
                  </span>
                </div>
                <h2 class="card-title text-base font-semibold leading-snug line-clamp-2">
                  ${msg.subject}
                </h2>
                <p class="text-sm text-base-content/70 line-clamp-2">
                  ${msg.intro}
                </p>
                <div class="card-actions justify-between items-center mt-2">
                  <span class="text-xs text-base-content/50">
                    ${msg.date ?? ""}
                  </span>
                  <button class="btn btn-primary btn-sm">
                    Open
                  </button>
                </div>
              </div>
            </div>
        `
        list.appendChild(li);
    });
}

window.addEventListener("DOMContentLoaded", async () => {
    const account = await createTempMail();

    if (account) {
        currentToken = account.token;

        document.getElementById("email-display").innerText = account.email;

        const refreshBtn = document.getElementById("refresh-btn");
        refreshBtn.disabled = false;
        refreshBtn.addEventListener("click", () => checkInbox(currentToken));

        await checkInbox(currentToken);

        setInterval(() => {
            checkInbox(currentToken);
        }, 5000);
    }
});
