import { Hono } from 'hono'
import { Navbar } from '../components/navbar'

const app = new Hono()

app.get('/', (c) => {
    return c.render(
        <>
            <Navbar />
            <main className="bg-primary">
                <h1>Page</h1>
                <p>Page of this site.</p>
            </main>
        </>,
        { title: 'Page' }
    )
})

export default app
