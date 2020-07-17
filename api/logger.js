require('dotenv').config()
const WebSocket = require('ws')
const ObjectsToCsv = require('objects-to-csv')

const WS_PORT = process.env.WS_PORT

const wss = new WebSocket.Server({ port: WS_PORT })


data = []

wss.on('connection', (ws) => {
  console.log('arduino connected')

  ws.on('message', (message) => {
    data.push(JSON.parse(message))
    console.log(data.length)
    if (data.length > 0 && data.length % 1000 === 0) {
      const csv = new ObjectsToCsv(data)
      data = []
      saveData(csv)
    }
  })

  ws.send('connected')
})

const saveData = async (data) => {
  await csv.toDisk('data.csv', { append: true })
  console.log('data saved')
}
