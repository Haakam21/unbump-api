const infoRouter = require('express').Router()

potholesRouter.get('/', async (request, response) => {
  const info = { videoURL: "https://www.youtube.com/embed/1aPPNK6nmck", text: "hello!" }

  response.send(info)
})

module.exports = infoRouter
