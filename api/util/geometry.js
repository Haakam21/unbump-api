function coordsDistM(coords0, coords1) {
  var dLat = toRad(coords1.latitude - coords0.latitude);
  var dLon = toRad(coords1.longitude - coords0.longitude);
  var lat1 = toRad(coords0.latitude);
  var lat2 = toRad(coords1.latitude);

  var a = Math.pow(Math.sin(dLat / 2), 2) + Math.pow(Math.sin(dLon / 2), 2) * Math.cos(lat1) * Math.cos(lat2);
  return 12746000 * Math.atan2(Math.sqrt(a), Math.sqrt(1 - a)); //units: meters
}

function toRad(degree) {
  return degree * Math.PI / 180;
}

module.exports = { coordsDistM, toRad }
