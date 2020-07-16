const cors = require('cors')
const express = require('express')
require('express-async-errors')

const potholesRouter = require('./controllers/potholes')

const app = express()

app.use(cors())
app.use(express.json())
app.use(express.static('public'))

app.use('/api/potholes', potholesRouter)

module.exports = app
