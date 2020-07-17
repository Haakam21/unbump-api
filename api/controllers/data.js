const dataRouter = require('express').Router()

dataRouter.get('/', async (request, response) => {
  response.download('data.csv');
})

module.exports = dataRouter
