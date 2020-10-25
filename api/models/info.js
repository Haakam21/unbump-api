const mongoose = require('mongoose')

const infoSchema = new mongoose.Schema({
  videoURL: {
    type: String,
    required: true
  },
  text: {
    type: String,
    required: true
  }
})

infoSchema.set('toJSON', {
  transform: (document, returnedObject) => {
    returnedObject.id = returnedObject._id.toString()
    delete returnedObject._id
    delete returnedObject.__v
  }
})

const Info = mongoose.model('Info', infoSchema)

module.exports = Info
