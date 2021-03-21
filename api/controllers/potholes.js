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
  
  // Check that request is valid
  if (!body.latitude || !body.longitude) {
    response.status(400).send({ error: 'Latitude or longitude undefined' })
  }

  // Send coordinates to the Mapbox Map Matching API to get the closest point on the road within 50 meters
  const point = { coordinates: [body.longitude, body.latitude], radius: 50 }
  const mapboxResponse = await mapMatchingService.getMatch({ points: [point, point] }).send()

  const latitude = mapboxResponse.body.tracepoints[0].location[1]
  const longitude = mapboxResponse.body.tracepoints[0].location[0]
  
  // Check that Mapbox Map Matching API response is valid
  if (!latitude || !longitude) {
    response.status(500).send({ error: 'Error with Mapbox Map Matching API' })
  }

  // Instantiate ruler and check for existing potholes within 5 meters
  // If an existing pothole is found withing 5 meters return that pothole
  const ruler = new CheapRuler(latitude, 'meters')
  const potholes = await Pothole.find()
  potholes.forEach(pothole => {
    if (ruler.distance([latitude, longitude], [pothole.latitude, pothole.longitude]) <= 5) {
      return response.status(200).send(pothole)
    }
  })

  // If no existing pothole is found withing 5 meters create a new pothole
  const pothole = new Pothole({
    latitude: latitude,
    longitude: longitude,
    date: new Date()
  })
  await pothole.save()

  // Return newly created pothole
  response.status(201).send(pothole)
  console.log(pothole)
})

module.exports = potholesRouter
