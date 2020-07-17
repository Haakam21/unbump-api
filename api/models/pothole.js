const mongoose = require('mongoose')

const potholeSchema = new mongoose.Schema({
  latitude: {
    type: Number,
    required: true
  },
  longitude: {
    type: Number,
    required: true
  },
  date: Date
})

potholeSchema.set('toJSON', {
  transform: (document, returnedObject) => {
    returnedObject.id = returnedObject._id.toString()
    delete returnedObject._id
    delete returnedObject.__v
  }
})

const Pothole = mongoose.model('Pothole', potholeSchema)

module.exports = Pothole
