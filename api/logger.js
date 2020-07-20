require('dotenv').config()
const WebSocket = require('ws')
const ObjectsToCsv = require('objects-to-csv')

const WS_PORT = process.env.WS_PORT

const wss = new WebSocket.Server({ port: WS_PORT })

wss.on('connection', (ws) => {
  console.log('arduino connected')
  data = []

  ws.on('message', (message) => {
    const row = JSON.parse(message)
    row.date = new Date()
    data.push(row)
    if (data.length > 0 && data.length % 100 === 0) {
      const csv = new ObjectsToCsv(data)
      data = []
      saveData(csv)
    }
  })

  ws.send('connected')

  ws.on('close', () => console.log('arduino disconnected'))
})

const saveData = async (csv) => {
  await csv.toDisk('model/data.csv', { append: true })
  console.log('data saved')
}
