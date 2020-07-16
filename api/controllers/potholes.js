const potholesRouter = require('express').Router()

const geometryUtil = require('../util/geometry')

const Pothole = require('../models/pothole')

potholesRouter.get('/', async (request, response) => {
  const potholes = await Pothole.find()

  response.send(potholes)
})

potholesRouter.post('/', async (request, response) => {
  const body = request.body

  const potholes = await Pothole.find()
  potholes.forEach(pothole => {
    if (geometryUtil.lngLatDist(body, pothole) < 0.000001) {
      return response.send(pothole)
    }
  })

  const pothole = new Pothole({
    latitude: body.latitude,
    longitude: body.longitude,
    date: new Date()
  })
  await pothole.save()

  response.send(pothole)
  console.log(`pothole recorded`)
})

module.exports = potholesRouter
