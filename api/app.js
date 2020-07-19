const cors = require('cors')
const express = require('express')
require('express-async-errors')

const potholesRouter = require('./controllers/potholes')
const dataRouter = require('./controllers/data')

const app = express()

app.use(cors())
//app.use(express.json())
app.use(express.static('public'))

app.use('/api/potholes', potholesRouter)
app.use('/api/data', dataRouter)

module.exports = app
