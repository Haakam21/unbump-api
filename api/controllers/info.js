const infoRouter = require('express').Router()

const Info = require('../models/info')

infoRouter.get('/', async (request, response) => {
  const info = await Info.findOne()//{ videoURL: "https://www.youtube.com/embed/1aPPNK6nmck", text: "Hello World!" }

  response.send(info)
})

module.exports = infoRouter
