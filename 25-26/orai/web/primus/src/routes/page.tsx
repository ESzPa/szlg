import { Hono } from 'hono'

const app = new Hono()

app.get('/', (c) => {
    return c.render(
        <main>
            <h1>Page</h1>
            <p>Page of this site.</p>
        </main>,
        { title: 'Page' }
    )
})

export default app
