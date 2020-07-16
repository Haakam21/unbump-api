const lngLatDist = (coords0, coords1) => {
  return Math.sqrt((coords1.longitude - coords0.longitude) ** 2 + (coords1.latitude - coords0.latitude) ** 2)
}

module.exports = { lngLatDist }
