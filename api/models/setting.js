const mongoose = require('mongoose')

const settingSchema = new mongoose.Schema({
  minSpd: {
    type: Number,
    required: true
  },
  maxDist: {
    type: Number,
    required: true
  },
  maxAngSpd: {
    type: Number,
    required: true
  },
  minAccSqd: {
    type: Number,
    required: true
  },
  minImpSqd: {
    type: Number,
    required: true
  }
})

settingSchema.set('toJSON', {
  transform: (document, returnedObject) => {
    returnedObject.id = returnedObject._id.toString()
    delete returnedObject._id
    delete returnedObject.__v
  }
})

const setting = mongoose.model('Setting', settingSchema)

module.exports = setting
