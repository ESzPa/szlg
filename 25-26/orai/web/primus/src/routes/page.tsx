import { Hono } from 'hono'

const app = new Hono()

app.get('/', (c) => {
    return c.render(
        <div>
            <h1>Page</h1>
            <p>Page of this site.</p>
        </div>,
        { title: 'Page' }
    )
})

export default app
