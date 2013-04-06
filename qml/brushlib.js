function loadBrushPack() {
    var brushPack = coreLib.loadBrushPack()
    var jsonBrushPack = JSON.parse(brushPack)
    for (var i = 0; i < jsonBrushPack.length; i++) {
        libraryModel.append(jsonBrushPack[i])
    }
}
