/* AprilBrush - Digital Painting Software
 * Copyright (C) 2012-2013 Vladimir Zarypov <krre31@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

function loadBrushPack() {
    var brushPack = coreLib.loadBrushPack()
    var jsonBrushPack = JSON.parse(brushPack)
    for (var i = 0; i < jsonBrushPack.length; i++) {
        libraryModel.append(jsonBrushPack[i])
    }
}
