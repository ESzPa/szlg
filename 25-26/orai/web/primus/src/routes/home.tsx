import { Hono } from 'hono'

const app = new Hono()

app.get('/', (c) => {
    return c.render(
        <div>
            <h1>Home</h1>
            <p>Welcome!</p>
        </div>,
        { title: 'Home' }
    )
})

export default app
