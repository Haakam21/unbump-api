const settingsRouter = require('express').Router()

const Setting = require('../models/setting')

settingsRouter.get('/', async (request, response) => {
  const setting = await Setting.findOne()

  response.send(setting)
})

module.exports = settingsRouter
