const infoRouter = require('express').Router()

const Info = require('../models/info')

infoRouter.get('/', async (request, response) => {
  const info = await Info.findOne()

  response.send(info)
})

module.exports = infoRouter
