import { jsxRenderer } from 'hono/jsx-renderer'

declare module 'hono' {
    interface ContextRenderer {
        (content: string | Promise<string>, props?: { title?: string }): Response
    }
}

export const renderer = jsxRenderer(({ children, title }) => {
    return (
        <html lang="en">
            <head>
                <meta charset="UTF-8" />
                <meta name="viewport" content="width=device-width, initial-scale=1.0" />
                <link rel="stylesheet" href="/static/style.css" />
                <link href="https://cdn.jsdelivr.net/npm/daisyui@4.11.1/dist/full.min.css" rel="stylesheet" type="text/css" />
                <script src="https://cdn.tailwindcss.com"></script>
                <title>{title ?? 'Primus'}</title>
            </head>
            <body>
                {children}
            </body>
        </html>
    )
})
