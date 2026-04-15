import { Hono } from 'hono'
import { serveStatic } from 'hono/bun'
import { renderer } from './renderer'
import home from './routes/home'
import page from './routes/page'

const app = new Hono()

app.use('/static/*', serveStatic({ root: './' }))
app.use('*', renderer)

app.route('/', home)
app.route('/page', page)

export default app
