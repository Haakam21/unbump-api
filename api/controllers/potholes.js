const potholesRouter = require('express').Router()
const mapMatching = require('@mapbox/mapbox-sdk/services/map-matching')
const CheapRuler = require('cheap-ruler')

const mapMatchingService = mapMatching({ accessToken: 'pk.eyJ1IjoiaGFha2FtMjEiLCJhIjoiY2tjbmlqamJ6MGI4dDM0bGJlNjMyNjZrYSJ9.akOmoDir6UBVboKQnLsIXg' })

const Pothole = require('../models/pothole')

potholesRouter.get('/', async (request, response) => {
  const potholes = await Pothole.find()

  response.send(potholes)
})

potholesRouter.post('/', async (request, response) => {
  const body = request.body

  try {
    const point = { coordinates: [body.longitude, body.latitude], radius: 50 }

    const mapboxResponse = await mapMatchingService.getMatch({ points: [point, point] }).send()

    const latitude = mapboxResponse.body.tracepoints[0].location[1]
    const longitude = mapboxResponse.body.tracepoints[0].location[0]

    const ruler = new CheapRuler(latitude, 'meters')

    const potholes = await Pothole.find()
    potholes.forEach(pothole => {
      if (ruler.distance([latitude, longitude], [pothole.latitude, pothole.longitude]) < 1) {
        return response.send(pothole)
      }
    })

    const pothole = new Pothole({
      latitude: latitude,
      longitude: longitude,
      date: new Date()
    })
    await pothole.save()

    response.send(pothole)
    console.log('pothole recorded')
  } catch {
    response.send({ error: 'failed to record pothole' })
    console.log('pothole error')
  }
})

module.exports = potholesRouter
