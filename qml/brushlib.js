function loadBrushPack() {
    var brushPack = coreLib.brushPack()
    var jsonBrushPack = JSON.parse(brushPack)
    for (var i = 0; i < jsonBrushPack.length; i++) {
        libraryModel.append(jsonBrushPack[i])
    }
}
