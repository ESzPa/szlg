import { Hono } from 'hono'

const app = new Hono()

app.get('/', (c) => {
    return c.render(
        <main>
            <form className="bg-neutral-content text-neutral">
                <h2>Login</h2>
                <a className="btn btn-ghost">Submit</a>
            </form>
        </main>,
        { title: 'Home' }
    )
})

export default app
