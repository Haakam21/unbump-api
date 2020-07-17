require('dotenv').config()
require('./logger')
const app = require('./app')
const mongoose = require('mongoose')

const PORT = process.env.PORT
const DB_URI = process.env.MONGODB_URI

app.listen(PORT, function() {
  console.log(`server running on ${PORT}`)
})

mongoose.connect(DB_URI, {useNewUrlParser: true, useUnifiedTopology: true}).then(result => {
  console.log('successfully connected to MongoDB')
})
.catch((error) => {
  console.log('failed to connect to MongoDB:', error.message)
})
