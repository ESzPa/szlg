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
                <title>{title ?? 'Primus'}</title>
            </head>
            <body>
                <nav>
                    <a href="/">Home</a>
                    <a href="/page">Page</a>
                </nav>
                <main>{children}</main>
            </body>
        </html>
    )
})
