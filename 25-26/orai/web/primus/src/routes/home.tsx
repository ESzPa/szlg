import { Hono } from 'hono'
import { Navbar } from '../components/navbar'

const app = new Hono()

app.get('/', (c) => {
    return c.render(
        <>
            <Navbar />
            <main className="bg-primary">
                <h1>Home</h1>
                <p>Welcome!</p>
            </main>
        </>,
        { title: 'Home' }
    )
})

export default app
