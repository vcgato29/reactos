@ stdcall GdipAddPathArc(ptr long long long long long long)
@ stdcall GdipAddPathArcI(ptr long long long long long long)
@ stdcall GdipAddPathBezier(ptr long long long long long long long long)
@ stdcall GdipAddPathBezierI(ptr long long long long long long long long)
@ stdcall GdipAddPathBeziers(ptr ptr long)
@ stdcall GdipAddPathBeziersI(ptr ptr long)
@ stdcall GdipAddPathClosedCurve2(ptr ptr long long)
@ stdcall GdipAddPathClosedCurve2I(ptr ptr long long)
@ stdcall GdipAddPathClosedCurve(ptr ptr long)
@ stdcall GdipAddPathClosedCurveI(ptr ptr long)
@ stdcall GdipAddPathCurve2(ptr ptr long long)
@ stdcall GdipAddPathCurve2I(ptr ptr long long)
@ stub GdipAddPathCurve3
@ stub GdipAddPathCurve3I
@ stdcall GdipAddPathCurve(ptr ptr long)
@ stdcall GdipAddPathCurveI(ptr ptr long)
@ stdcall GdipAddPathEllipse(ptr long long long long)
@ stdcall GdipAddPathEllipseI(ptr long long long long)
@ stdcall GdipAddPathLine2(ptr ptr long)
@ stdcall GdipAddPathLine2I(ptr ptr long)
@ stdcall GdipAddPathLine(ptr long long long long)
@ stdcall GdipAddPathLineI(ptr long long long long)
@ stdcall GdipAddPathPath(ptr ptr long)
@ stub GdipAddPathPie
@ stub GdipAddPathPieI
@ stdcall GdipAddPathPolygon(ptr ptr long)
@ stdcall GdipAddPathPolygonI(ptr ptr long)
@ stdcall GdipAddPathRectangle(ptr long long long long)
@ stdcall GdipAddPathRectangleI(ptr long long long long)
@ stdcall GdipAddPathRectangles(ptr ptr long)
@ stdcall GdipAddPathRectanglesI(ptr ptr long)
@ stub GdipAddPathString
@ stub GdipAddPathStringI
@ stdcall GdipAlloc(long)
@ stub GdipBeginContainer2
@ stub GdipBeginContainer
@ stub GdipBeginContainerI
@ stub GdipBitmapApplyEffect
@ stub GdipBitmapConvertFormat
@ stub GdipBitmapCreateApplyEffect
@ stub GdipBitmapGetHistogram
@ stub GdipBitmapGetHistogramSize
@ stdcall GdipBitmapGetPixel(ptr long long ptr)
@ stdcall GdipBitmapLockBits(ptr ptr long long ptr)
@ stub GdipBitmapSetPixel
@ stub GdipBitmapSetResolution
@ stdcall GdipBitmapUnlockBits(ptr ptr)
@ stdcall GdipClearPathMarkers(ptr)
@ stub GdipCloneBitmapArea
@ stub GdipCloneBitmapAreaI
@ stdcall GdipCloneBrush(ptr ptr)
@ stdcall GdipCloneCustomLineCap(ptr ptr)
@ stdcall GdipCloneFont(ptr ptr)
@ stdcall GdipCloneFontFamily(ptr ptr)
@ stdcall GdipCloneImage(ptr ptr)
@ stdcall GdipCloneImageAttributes(ptr ptr)
@ stdcall GdipCloneMatrix(ptr ptr)
@ stdcall GdipClonePath(ptr ptr)
@ stdcall GdipClonePen(ptr ptr)
@ stdcall GdipCloneRegion(ptr ptr)
@ stdcall GdipCloneStringFormat(ptr ptr)
@ stdcall GdipClosePathFigure(ptr)
@ stdcall GdipClosePathFigures(ptr)
@ stdcall GdipCombineRegionPath(ptr ptr long)
@ stdcall GdipCombineRegionRect(ptr ptr long)
@ stdcall GdipCombineRegionRectI(ptr ptr long)
@ stdcall GdipCombineRegionRegion(ptr ptr long)
@ stub GdipComment
@ stdcall GdipConvertToEmfPlus(ptr ptr ptr long ptr ptr)
@ stub GdipConvertToEmfPlusToFile
@ stub GdipConvertToEmfPlusToStream
@ stub GdipCreateAdjustableArrowCap
@ stub GdipCreateBitmapFromDirectDrawSurface
@ stdcall GdipCreateBitmapFromFile(wstr ptr)
@ stdcall GdipCreateBitmapFromFileICM(wstr ptr)
@ stdcall GdipCreateBitmapFromGdiDib(ptr ptr ptr)
@ stdcall GdipCreateBitmapFromGraphics(long long ptr ptr)
@ stdcall GdipCreateBitmapFromHBITMAP(long long ptr)
@ stub GdipCreateBitmapFromHICON
@ stdcall GdipCreateBitmapFromResource(long wstr ptr)
@ stdcall GdipCreateBitmapFromScan0(long long long long ptr ptr)
@ stdcall GdipCreateBitmapFromStream(ptr ptr)
@ stdcall GdipCreateBitmapFromStreamICM(ptr ptr)
@ stub GdipCreateCachedBitmap
@ stdcall GdipCreateCustomLineCap(ptr ptr long long ptr)
@ stub GdipCreateEffect
@ stdcall GdipCreateFont(ptr long long long ptr)
@ stdcall GdipCreateFontFamilyFromName(wstr ptr ptr)
@ stdcall GdipCreateFontFromDC(long ptr)
@ stdcall GdipCreateFontFromLogfontA(long ptr ptr)
@ stdcall GdipCreateFontFromLogfontW(long ptr ptr)
@ stdcall GdipCreateFromHDC2(long long ptr)
@ stdcall GdipCreateFromHDC(long ptr)
@ stdcall GdipCreateFromHWND(long ptr)
@ stdcall GdipCreateFromHWNDICM(long ptr)
@ stdcall GdipCreateHBITMAPFromBitmap(ptr ptr long)
@ stub GdipCreateHICONFromBitmap
@ stub GdipCreateHalftonePalette
@ stub GdipCreateHatchBrush
@ stdcall GdipCreateImageAttributes(ptr)
@ stdcall GdipCreateLineBrush(ptr ptr long long long ptr)
@ stdcall GdipCreateLineBrushFromRect(ptr long long long long ptr)
@ stdcall GdipCreateLineBrushFromRectI(ptr long long long long ptr)
@ stdcall GdipCreateLineBrushFromRectWithAngle(ptr long long long long long ptr)
@ stdcall GdipCreateLineBrushFromRectWithAngleI(ptr long long long long long ptr)
@ stdcall GdipCreateLineBrushI(ptr ptr long long long ptr)
@ stdcall GdipCreateMatrix2(long long long long long long ptr)
@ stdcall GdipCreateMatrix3(ptr ptr ptr)
@ stdcall GdipCreateMatrix3I(ptr ptr ptr)
@ stdcall GdipCreateMatrix(ptr)
@ stdcall GdipCreateMetafileFromEmf(ptr long ptr)
@ stub GdipCreateMetafileFromFile
@ stub GdipCreateMetafileFromStream
@ stdcall GdipCreateMetafileFromWmf(ptr long ptr ptr)
@ stdcall GdipCreateMetafileFromWmfFile(wstr ptr ptr)
@ stdcall GdipCreatePath2(ptr ptr long long ptr)
@ stdcall GdipCreatePath2I(ptr ptr long long ptr)
@ stdcall GdipCreatePath(long ptr)
@ stdcall GdipCreatePathGradient(ptr long long ptr)
@ stdcall GdipCreatePathGradientFromPath(ptr ptr)
@ stdcall GdipCreatePathGradientI(ptr long long ptr)
@ stdcall GdipCreatePathIter(ptr ptr)
@ stdcall GdipCreatePen1(long long long ptr)
@ stdcall GdipCreatePen2(ptr long long ptr)
@ stdcall GdipCreateRegion(ptr)
@ stdcall GdipCreateRegionHrgn(ptr ptr)
@ stdcall GdipCreateRegionPath(ptr ptr)
@ stdcall GdipCreateRegionRect(ptr ptr)
@ stdcall GdipCreateRegionRectI(ptr ptr)
@ stdcall GdipCreateRegionRgnData(ptr long ptr)
@ stdcall GdipCreateSolidFill(long ptr)
@ stdcall GdipCreateStreamOnFile(ptr long ptr)
@ stdcall GdipCreateStringFormat(long long ptr)
@ stub GdipCreateTexture2
@ stub GdipCreateTexture2I
@ stub GdipCreateTexture
@ stdcall GdipCreateTextureIA(ptr ptr long long long long ptr)
@ stdcall GdipCreateTextureIAI(ptr ptr long long long long ptr)
@ stdcall GdipDeleteBrush(ptr)
@ stub GdipDeleteCachedBitmap
@ stdcall GdipDeleteCustomLineCap(ptr)
@ stub GdipDeleteEffect
@ stdcall GdipDeleteFont(ptr)
@ stdcall GdipDeleteFontFamily(ptr)
@ stdcall GdipDeleteGraphics(ptr)
@ stdcall GdipDeleteMatrix(ptr)
@ stdcall GdipDeletePath(ptr)
@ stdcall GdipDeletePathIter(ptr)
@ stdcall GdipDeletePen(ptr)
@ stdcall GdipDeletePrivateFontCollection(ptr)
@ stdcall GdipDeleteRegion(ptr)
@ stdcall GdipDeleteStringFormat(ptr)
@ stdcall GdipDisposeImage(ptr)
@ stdcall GdipDisposeImageAttributes(ptr)
@ stdcall GdipDrawArc(ptr ptr long long long long long long)
@ stdcall GdipDrawArcI(ptr ptr long long long long long long)
@ stdcall GdipDrawBezier(ptr ptr long long long long long long long long)
@ stdcall GdipDrawBezierI(ptr ptr long long long long long long long long)
@ stdcall GdipDrawBeziers(ptr ptr ptr long)
@ stdcall GdipDrawBeziersI(ptr ptr ptr long)
@ stub GdipDrawCachedBitmap
@ stdcall GdipDrawClosedCurve2(ptr ptr ptr long long)
@ stdcall GdipDrawClosedCurve2I(ptr ptr ptr long long)
@ stdcall GdipDrawClosedCurve(ptr ptr ptr long)
@ stdcall GdipDrawClosedCurveI(ptr ptr ptr long)
@ stdcall GdipDrawCurve2(ptr ptr ptr long long)
@ stdcall GdipDrawCurve2I(ptr ptr ptr long long)
@ stub GdipDrawCurve3
@ stub GdipDrawCurve3I
@ stdcall GdipDrawCurve(ptr ptr ptr long)
@ stdcall GdipDrawCurveI(ptr ptr ptr long)
@ stub GdipDrawDriverString
@ stdcall GdipDrawEllipse(ptr ptr long long long long)
@ stdcall GdipDrawEllipseI(ptr ptr long long long long)
@ stdcall GdipDrawImage(ptr ptr long long)
@ stub GdipDrawImageFX
@ stdcall GdipDrawImageI(ptr ptr long long)
@ stub GdipDrawImagePointRect
@ stub GdipDrawImagePointRectI
@ stub GdipDrawImagePoints
@ stub GdipDrawImagePointsI
@ stdcall GdipDrawImagePointsRect(ptr ptr ptr long long long long long long ptr ptr ptr)
@ stdcall GdipDrawImagePointsRectI(ptr ptr ptr long long long long long long ptr ptr ptr)
@ stdcall GdipDrawImageRect(ptr ptr long long long long)
@ stdcall GdipDrawImageRectI(ptr ptr long long long long)
@ stdcall GdipDrawImageRectRect(ptr ptr long long long long long long long long long ptr long ptr)
@ stdcall GdipDrawImageRectRectI(ptr ptr long long long long long long long long long ptr long ptr)
@ stdcall GdipDrawLine(ptr ptr long long long long)
@ stdcall GdipDrawLineI(ptr ptr long long long long)
@ stdcall GdipDrawLines(ptr ptr ptr long)
@ stdcall GdipDrawLinesI(ptr ptr ptr long)
@ stdcall GdipDrawPath(ptr ptr ptr)
@ stdcall GdipDrawPie(ptr ptr long long long long long long)
@ stdcall GdipDrawPieI(ptr ptr long long long long long long)
@ stdcall GdipDrawPolygon(ptr ptr ptr long)
@ stdcall GdipDrawPolygonI(ptr ptr ptr long)
@ stdcall GdipDrawRectangle(ptr ptr long long long long)
@ stdcall GdipDrawRectangleI(ptr ptr long long long long)
@ stdcall GdipDrawRectangles(ptr ptr ptr long)
@ stdcall GdipDrawRectanglesI(ptr ptr ptr long)
@ stdcall GdipDrawString(ptr ptr long ptr ptr ptr ptr)
@ stub GdipEmfToWmfBits
@ stub GdipEndContainer
@ stub GdipEnumerateMetafileDestPoint
@ stub GdipEnumerateMetafileDestPointI
@ stub GdipEnumerateMetafileDestPoints
@ stub GdipEnumerateMetafileDestPointsI
@ stub GdipEnumerateMetafileDestRect
@ stub GdipEnumerateMetafileDestRectI
@ stub GdipEnumerateMetafileSrcRectDestPoint
@ stub GdipEnumerateMetafileSrcRectDestPointI
@ stub GdipEnumerateMetafileSrcRectDestPoints
@ stub GdipEnumerateMetafileSrcRectDestPointsI
@ stub GdipEnumerateMetafileSrcRectDestRect
@ stub GdipEnumerateMetafileSrcRectDestRectI
@ stub GdipFillClosedCurve2
@ stub GdipFillClosedCurve2I
@ stub GdipFillClosedCurve
@ stub GdipFillClosedCurveI
@ stdcall GdipFillEllipse(ptr ptr long long long long)
@ stdcall GdipFillEllipseI(ptr ptr long long long long)
@ stdcall GdipFillPath(ptr ptr ptr)
@ stdcall GdipFillPie(ptr ptr long long long long long long)
@ stdcall GdipFillPieI(ptr ptr long long long long long long)
@ stdcall GdipFillPolygon2(ptr ptr ptr long)
@ stdcall GdipFillPolygon2I(ptr ptr ptr long)
@ stdcall GdipFillPolygon(ptr ptr ptr long long)
@ stdcall GdipFillPolygonI(ptr ptr ptr long long)
@ stdcall GdipFillRectangle(ptr ptr long long long long)
@ stdcall GdipFillRectangleI(ptr ptr long long long long)
@ stdcall GdipFillRectangles(ptr ptr ptr long)
@ stdcall GdipFillRectanglesI(ptr ptr ptr long)
@ stdcall GdipFillRegion(ptr ptr ptr)
@ stdcall GdipFindFirstImageItem(ptr ptr)
@ stub GdipFindNextImageItem
@ stub GdipFlattenPath
@ stdcall GdipFlush(ptr long)
@ stdcall GdipFree(ptr)
@ stub GdipGetAdjustableArrowCapFillState
@ stub GdipGetAdjustableArrowCapHeight
@ stub GdipGetAdjustableArrowCapMiddleInset
@ stub GdipGetAdjustableArrowCapWidth
@ stub GdipGetAllPropertyItems
@ stdcall GdipGetBrushType(ptr ptr)
@ stdcall GdipGetCellAscent(ptr long ptr)
@ stdcall GdipGetCellDescent(ptr long ptr)
@ stdcall GdipGetClip(ptr ptr)
@ stub GdipGetClipBounds
@ stub GdipGetClipBoundsI
@ stdcall GdipGetCompositingMode(ptr ptr)
@ stdcall GdipGetCompositingQuality(ptr ptr)
@ stdcall GdipGetCustomLineCapBaseCap(ptr ptr)
@ stdcall GdipGetCustomLineCapBaseInset(ptr ptr)
@ stub GdipGetCustomLineCapStrokeCaps
@ stdcall GdipGetCustomLineCapStrokeJoin(ptr ptr)
@ stub GdipGetCustomLineCapType
@ stdcall GdipGetCustomLineCapWidthScale(ptr ptr)
@ stdcall GdipGetDC(ptr ptr)
@ stdcall GdipGetDpiX(ptr ptr)
@ stdcall GdipGetDpiY(ptr ptr)
@ stub GdipGetEffectParameterSize
@ stub GdipGetEffectParameters
@ stdcall GdipGetEmHeight(ptr long ptr)
@ stub GdipGetEncoderParameterList
@ stub GdipGetEncoderParameterListSize
@ stub GdipGetFamily
@ stdcall GdipGetFamilyName(ptr ptr long)
@ stdcall GdipGetFontCollectionFamilyCount(ptr ptr)
@ stdcall GdipGetFontCollectionFamilyList(ptr long ptr ptr)
@ stub GdipGetFontHeight
@ stdcall GdipGetFontHeightGivenDPI(ptr long ptr)
@ stdcall GdipGetFontSize(ptr ptr)
@ stub GdipGetFontStyle
@ stdcall GdipGetFontUnit(ptr ptr)
@ stdcall GdipGetGenericFontFamilyMonospace(ptr)
@ stdcall GdipGetGenericFontFamilySansSerif(ptr)
@ stdcall GdipGetGenericFontFamilySerif(ptr)
@ stub GdipGetHatchBackgroundColor
@ stub GdipGetHatchForegroundColor
@ stub GdipGetHatchStyle
@ stub GdipGetHemfFromMetafile
@ stub GdipGetImageAttributesAdjustedPalette
@ stdcall GdipGetImageBounds(ptr ptr ptr)
@ stub GdipGetImageDecoders
@ stub GdipGetImageDecodersSize
@ stdcall GdipGetImageDimension(ptr ptr ptr)
@ stdcall GdipGetImageEncoders(long long ptr)
@ stdcall GdipGetImageEncodersSize(ptr ptr)
@ stdcall GdipGetImageFlags(ptr ptr)
@ stdcall GdipGetImageGraphicsContext(ptr ptr)
@ stdcall GdipGetImageHeight(ptr ptr)
@ stdcall GdipGetImageHorizontalResolution(ptr ptr)
@ stub GdipGetImageItemData
@ stub GdipGetImagePalette
@ stub GdipGetImagePaletteSize
@ stdcall GdipGetImagePixelFormat(ptr ptr)
@ stdcall GdipGetImageRawFormat(ptr ptr)
@ stub GdipGetImageThumbnail
@ stdcall GdipGetImageType(ptr ptr)
@ stdcall GdipGetImageVerticalResolution(ptr ptr)
@ stdcall GdipGetImageWidth(ptr ptr)
@ stdcall GdipGetInterpolationMode(ptr ptr)
@ stub GdipGetLineBlend
@ stub GdipGetLineBlendCount
@ stdcall GdipGetLineColors(ptr ptr)
@ stdcall GdipGetLineGammaCorrection(ptr ptr)
@ stub GdipGetLinePresetBlend
@ stub GdipGetLinePresetBlendCount
@ stdcall GdipGetLineRect(ptr ptr)
@ stdcall GdipGetLineRectI(ptr ptr)
@ stdcall GdipGetLineSpacing(ptr long ptr)
@ stub GdipGetLineTransform
@ stdcall GdipGetLineWrapMode(ptr ptr)
@ stub GdipGetLogFontA
@ stdcall GdipGetLogFontW(ptr ptr ptr)
@ stdcall GdipGetMatrixElements(ptr ptr)
@ stub GdipGetMetafileDownLevelRasterizationLimit
@ stub GdipGetMetafileHeaderFromEmf
@ stub GdipGetMetafileHeaderFromFile
@ stdcall GdipGetMetafileHeaderFromMetafile(ptr ptr)
@ stub GdipGetMetafileHeaderFromStream
@ stub GdipGetMetafileHeaderFromWmf
@ stub GdipGetNearestColor
@ stdcall GdipGetPageScale(ptr ptr)
@ stdcall GdipGetPageUnit(ptr ptr)
@ stdcall GdipGetPathData(ptr ptr)
@ stdcall GdipGetPathFillMode(ptr ptr)
@ stdcall GdipGetPathGradientBlend(ptr ptr ptr long)
@ stdcall GdipGetPathGradientBlendCount(ptr ptr)
@ stub GdipGetPathGradientCenterColor
@ stdcall GdipGetPathGradientCenterPoint(ptr ptr)
@ stdcall GdipGetPathGradientCenterPointI(ptr ptr)
@ stdcall GdipGetPathGradientFocusScales(ptr ptr ptr)
@ stdcall GdipGetPathGradientGammaCorrection(ptr ptr)
@ stub GdipGetPathGradientPath
@ stdcall GdipGetPathGradientPointCount(ptr ptr)
@ stub GdipGetPathGradientPresetBlend
@ stub GdipGetPathGradientPresetBlendCount
@ stdcall GdipGetPathGradientRect(ptr ptr)
@ stdcall GdipGetPathGradientRectI(ptr ptr)
@ stub GdipGetPathGradientSurroundColorCount
@ stdcall GdipGetPathGradientSurroundColorsWithCount(ptr ptr ptr)
@ stub GdipGetPathGradientTransform
@ stdcall GdipGetPathGradientWrapMode(ptr ptr)
@ stdcall GdipGetPathLastPoint(ptr ptr)
@ stdcall GdipGetPathPoints(ptr ptr long)
@ stdcall GdipGetPathPointsI(ptr ptr long)
@ stdcall GdipGetPathTypes(ptr ptr long)
@ stdcall GdipGetPathWorldBounds(ptr ptr ptr ptr)
@ stdcall GdipGetPathWorldBoundsI(ptr ptr ptr ptr)
@ stdcall GdipGetPenBrushFill(ptr ptr)
@ stdcall GdipGetPenColor(ptr ptr)
@ stub GdipGetPenCompoundArray
@ stub GdipGetPenCompoundCount
@ stdcall GdipGetPenCustomEndCap(ptr ptr)
@ stdcall GdipGetPenCustomStartCap(ptr ptr)
@ stdcall GdipGetPenDashArray(ptr ptr long)
@ stdcall GdipGetPenDashCap197819(ptr ptr)
@ stdcall GdipGetPenDashCount(ptr ptr)
@ stdcall GdipGetPenDashOffset(ptr ptr)
@ stdcall GdipGetPenDashStyle(ptr ptr)
@ stdcall GdipGetPenEndCap(ptr ptr)
@ stub GdipGetPenFillType
@ stdcall GdipGetPenLineJoin(ptr ptr)
@ stdcall GdipGetPenMiterLimit(ptr ptr)
@ stdcall GdipGetPenMode(ptr ptr)
@ stdcall GdipGetPenStartCap(ptr ptr)
@ stub GdipGetPenTransform
@ stdcall GdipGetPenUnit(ptr ptr)
@ stdcall GdipGetPenWidth(ptr ptr)
@ stdcall GdipGetPixelOffsetMode(ptr ptr)
@ stdcall GdipGetPointCount(ptr ptr)
@ stub GdipGetPropertyCount
@ stub GdipGetPropertyIdList
@ stub GdipGetPropertyItem
@ stdcall GdipGetPropertyItemSize(ptr long ptr)
@ stub GdipGetPropertySize
@ stdcall GdipGetRegionBounds(ptr ptr ptr)
@ stdcall GdipGetRegionBoundsI(ptr ptr ptr)
@ stdcall GdipGetRegionData(ptr ptr long ptr)
@ stdcall GdipGetRegionDataSize(ptr ptr)
@ stdcall GdipGetRegionHRgn(ptr ptr ptr)
@ stub GdipGetRegionScans
@ stub GdipGetRegionScansCount
@ stub GdipGetRegionScansI
@ stub GdipGetRenderingOrigin
@ stdcall GdipGetSmoothingMode(ptr ptr)
@ stdcall GdipGetSolidFillColor(ptr ptr)
@ stdcall GdipGetStringFormatAlign(ptr ptr)
@ stdcall GdipGetStringFormatDigitSubstitution(ptr ptr ptr)
@ stdcall GdipGetStringFormatFlags(ptr ptr)
@ stdcall GdipGetStringFormatHotkeyPrefix(ptr ptr)
@ stdcall GdipGetStringFormatLineAlign(ptr ptr)
@ stdcall GdipGetStringFormatMeasurableCharacterRangeCount(ptr ptr)
@ stdcall GdipGetStringFormatTabStopCount(ptr ptr)
@ stdcall GdipGetStringFormatTabStops(ptr long ptr ptr)
@ stdcall GdipGetStringFormatTrimming(ptr ptr)
@ stub GdipGetTextContrast
@ stdcall GdipGetTextRenderingHint(ptr ptr)
@ stub GdipGetTextureImage
@ stub GdipGetTextureTransform
@ stub GdipGetTextureWrapMode
@ stub GdipGetVisibleClipBounds
@ stub GdipGetVisibleClipBoundsI
@ stdcall GdipGetWorldTransform(ptr ptr)
@ stub GdipGraphicsClear
@ stub GdipGraphicsSetAbort
@ stub GdipImageForceValidation
@ stdcall GdipImageGetFrameCount(ptr ptr ptr)
@ stdcall GdipImageGetFrameDimensionsCount(ptr ptr)
@ stdcall GdipImageGetFrameDimensionsList(ptr ptr long)
@ stub GdipImageRotateFlip
@ stdcall GdipImageSelectActiveFrame(ptr ptr long)
@ stub GdipImageSetAbort
@ stub GdipInitializePalette
@ stdcall GdipInvertMatrix(ptr)
@ stub GdipIsClipEmpty
@ stdcall GdipIsEmptyRegion(ptr ptr ptr)
@ stdcall GdipIsEqualRegion(ptr ptr ptr ptr)
@ stdcall GdipIsInfiniteRegion(ptr ptr ptr)
@ stdcall GdipIsMatrixEqual(ptr ptr ptr)
@ stdcall GdipIsMatrixIdentity(ptr ptr)
@ stdcall GdipIsMatrixInvertible(ptr ptr)
@ stdcall GdipIsOutlineVisiblePathPoint(ptr long long ptr ptr ptr)
@ stdcall GdipIsOutlineVisiblePathPointI(ptr long long ptr ptr ptr)
@ stdcall GdipIsStyleAvailable(ptr long ptr)
@ stub GdipIsVisibleClipEmpty
@ stdcall GdipIsVisiblePathPoint(ptr long long ptr ptr)
@ stdcall GdipIsVisiblePathPointI(ptr long long ptr ptr)
@ stub GdipIsVisiblePoint
@ stub GdipIsVisiblePointI
@ stub GdipIsVisibleRect
@ stub GdipIsVisibleRectI
@ stub GdipIsVisibleRegionPoint
@ stub GdipIsVisibleRegionPointI
@ stub GdipIsVisibleRegionRect
@ stub GdipIsVisibleRegionRectI
@ stdcall GdipLoadImageFromFile(wstr ptr)
@ stdcall GdipLoadImageFromFileICM(wstr ptr)
@ stdcall GdipLoadImageFromStream(ptr ptr)
@ stdcall GdipLoadImageFromStreamICM(ptr ptr)
@ stdcall GdipMeasureCharacterRanges(ptr wstr long ptr ptr ptr long ptr)
@ stub GdipMeasureDriverString
@ stdcall GdipMeasureString(ptr wstr long ptr ptr ptr ptr ptr ptr)
@ stub GdipMultiplyLineTransform
@ stdcall GdipMultiplyMatrix(ptr ptr long)
@ stub GdipMultiplyPathGradientTransform
@ stub GdipMultiplyPenTransform
@ stub GdipMultiplyTextureTransform
@ stdcall GdipMultiplyWorldTransform(ptr ptr long)
@ stub GdipNewInstalledFontCollection
@ stdcall GdipNewPrivateFontCollection(ptr)
@ stdcall GdipPathIterCopyData(ptr ptr ptr ptr long long)
@ stdcall GdipPathIterEnumerate(ptr ptr ptr ptr long)
@ stdcall GdipPathIterGetCount(ptr ptr)
@ stdcall GdipPathIterGetSubpathCount(ptr ptr)
@ stdcall GdipPathIterHasCurve(ptr ptr)
@ stub GdipPathIterIsValid
@ stdcall GdipPathIterNextMarker(ptr ptr ptr ptr)
@ stub GdipPathIterNextMarkerPath
@ stub GdipPathIterNextPathType
@ stdcall GdipPathIterNextSubpath(ptr ptr ptr ptr ptr)
@ stub GdipPathIterNextSubpathPath
@ stdcall GdipPathIterRewind(ptr)
@ stub GdipPlayMetafileRecord
@ stub GdipPlayTSClientRecord
@ stdcall GdipPrivateAddFontFile(ptr wstr)
@ stub GdipPrivateAddMemoryFont
@ stub GdipRecordMetafile
@ stub GdipRecordMetafileFileName
@ stub GdipRecordMetafileFileNameI
@ stub GdipRecordMetafileI
@ stub GdipRecordMetafileStream
@ stub GdipRecordMetafileStreamI
@ stdcall GdipReleaseDC(ptr ptr)
@ stdcall GdipRemovePropertyItem(ptr long)
@ stub GdipResetClip
@ stub GdipResetImageAttributes
@ stub GdipResetLineTransform
@ stub GdipResetPageTransform
@ stdcall GdipResetPath(ptr)
@ stub GdipResetPathGradientTransform
@ stub GdipResetPenTransform
@ stub GdipResetTextureTransform
@ stub GdipResetWorldTransform
@ stdcall GdipRestoreGraphics(ptr long)
@ stub GdipReversePath
@ stub GdipRotateLineTransform
@ stdcall GdipRotateMatrix(ptr long long)
@ stub GdipRotatePathGradientTransform
@ stub GdipRotatePenTransform
@ stub GdipRotateTextureTransform
@ stdcall GdipRotateWorldTransform(ptr long long)
@ stub GdipSaveAdd
@ stub GdipSaveAddImage
@ stdcall GdipSaveGraphics(ptr ptr)
@ stdcall GdipSaveImageToFile(ptr ptr ptr ptr)
@ stdcall GdipSaveImageToStream(ptr ptr ptr ptr)
@ stub GdipScaleLineTransform
@ stdcall GdipScaleMatrix(ptr long long long)
@ stub GdipScalePathGradientTransform
@ stub GdipScalePenTransform
@ stub GdipScaleTextureTransform
@ stdcall GdipScaleWorldTransform(ptr long long long)
@ stub GdipSetAdjustableArrowCapFillState
@ stub GdipSetAdjustableArrowCapHeight
@ stub GdipSetAdjustableArrowCapMiddleInset
@ stub GdipSetAdjustableArrowCapWidth
@ stub GdipSetClipGraphics
@ stub GdipSetClipHrgn
@ stub GdipSetClipPath
@ stub GdipSetClipRect
@ stdcall GdipSetClipRectI(ptr long long long long long)
@ stdcall GdipSetClipRegion(ptr ptr long)
@ stdcall GdipSetCompositingMode(ptr long)
@ stdcall GdipSetCompositingQuality(ptr long)
@ stdcall GdipSetCustomLineCapBaseCap(ptr long)
@ stdcall GdipSetCustomLineCapBaseInset(ptr long)
@ stdcall GdipSetCustomLineCapStrokeCaps(ptr long long)
@ stdcall GdipSetCustomLineCapStrokeJoin(ptr long)
@ stdcall GdipSetCustomLineCapWidthScale(ptr long)
@ stdcall GdipSetEffectParameters(ptr ptr long)
@ stdcall GdipSetEmpty(ptr)
@ stdcall GdipSetImageAttributesCachedBackground(ptr long)
@ stdcall GdipSetImageAttributesColorKeys(ptr long long long long)
@ stdcall GdipSetImageAttributesColorMatrix(ptr long long ptr ptr long)
@ stdcall GdipSetImageAttributesGamma(ptr long long long)
@ stdcall GdipSetImageAttributesNoOp(ptr long long)
@ stdcall GdipSetImageAttributesOutputChannel(ptr long long long)
@ stdcall GdipSetImageAttributesOutputChannelColorProfile(ptr long long ptr)
@ stdcall GdipSetImageAttributesRemapTable(ptr long long long ptr)
@ stdcall GdipSetImageAttributesThreshold(ptr long long long)
@ stdcall GdipSetImageAttributesToIdentity(ptr long)
@ stdcall GdipSetImageAttributesWrapMode(ptr long long long)
@ stdcall GdipSetImagePalette(ptr ptr)
@ stdcall GdipSetInfinite(ptr)
@ stdcall GdipSetInterpolationMode(ptr long)
@ stdcall GdipSetLineBlend(ptr ptr ptr long)
@ stdcall GdipSetLineColors(ptr long long)
@ stdcall GdipSetLineGammaCorrection(ptr long)
@ stdcall GdipSetLineLinearBlend(ptr long long)
@ stdcall GdipSetLinePresetBlend(ptr ptr ptr long)
@ stdcall GdipSetLineSigmaBlend(ptr long long)
@ stdcall GdipSetLineTransform(ptr ptr)
@ stdcall GdipSetLineWrapMode(ptr long)
@ stdcall GdipSetMatrixElements(ptr long long long long long long)
@ stdcall GdipSetMetafileDownLevelRasterizationLimit(ptr long)
@ stdcall GdipSetPageScale(ptr long)
@ stdcall GdipSetPageUnit(ptr long)
@ stdcall GdipSetPathFillMode(ptr long)
@ stub GdipSetPathGradientBlend
@ stdcall GdipSetPathGradientCenterColor(ptr long)
@ stdcall GdipSetPathGradientCenterPoint(ptr ptr)
@ stdcall GdipSetPathGradientCenterPointI(ptr ptr)
@ stdcall GdipSetPathGradientFocusScales(ptr long long)
@ stdcall GdipSetPathGradientGammaCorrection(ptr long)
@ stub GdipSetPathGradientLinearBlend
@ stub GdipSetPathGradientPath
@ stub GdipSetPathGradientPresetBlend
@ stdcall GdipSetPathGradientSigmaBlend(ptr long long)
@ stdcall GdipSetPathGradientSurroundColorsWithCount(ptr ptr ptr)
@ stub GdipSetPathGradientTransform
@ stdcall GdipSetPathGradientWrapMode(ptr long)
@ stdcall GdipSetPathMarker(ptr)
@ stdcall GdipSetPenBrushFill(ptr ptr)
@ stdcall GdipSetPenColor(ptr long)
@ stub GdipSetPenCompoundArray
@ stdcall GdipSetPenCustomEndCap(ptr ptr)
@ stdcall GdipSetPenCustomStartCap(ptr ptr)
@ stdcall GdipSetPenDashArray(ptr ptr long)
@ stdcall GdipSetPenDashCap197819(ptr long)
@ stdcall GdipSetPenDashOffset(ptr long)
@ stdcall GdipSetPenDashStyle(ptr long)
@ stdcall GdipSetPenEndCap(ptr long)
@ stdcall GdipSetPenLineCap197819(ptr long long long)
@ stdcall GdipSetPenLineJoin(ptr long)
@ stdcall GdipSetPenMiterLimit(ptr long)
@ stdcall GdipSetPenMode(ptr long)
@ stdcall GdipSetPenStartCap(ptr long)
@ stub GdipSetPenTransform
@ stub GdipSetPenUnit
@ stdcall GdipSetPenWidth(ptr long)
@ stdcall GdipSetPixelOffsetMode(ptr long)
@ stub GdipSetPropertyItem
@ stub GdipSetRenderingOrigin
@ stdcall GdipSetSmoothingMode(ptr long)
@ stdcall GdipSetSolidFillColor(ptr ptr)
@ stdcall GdipSetStringFormatAlign(ptr long)
@ stdcall GdipSetStringFormatDigitSubstitution(ptr long long)
@ stdcall GdipSetStringFormatFlags(ptr long)
@ stdcall GdipSetStringFormatHotkeyPrefix(ptr long)
@ stdcall GdipSetStringFormatLineAlign(ptr long)
@ stdcall GdipSetStringFormatMeasurableCharacterRanges(ptr long ptr)
@ stdcall GdipSetStringFormatTabStops(ptr long long ptr)
@ stdcall GdipSetStringFormatTrimming(ptr long)
@ stub GdipSetTextContrast
@ stdcall GdipSetTextRenderingHint(ptr long)
@ stdcall GdipSetTextureTransform(ptr ptr)
@ stub GdipSetTextureWrapMode
@ stdcall GdipSetWorldTransform(ptr ptr)
@ stdcall GdipShearMatrix(ptr long long long)
@ stdcall GdipStartPathFigure(ptr)
@ stdcall GdipStringFormatGetGenericDefault(ptr)
@ stdcall GdipStringFormatGetGenericTypographic(ptr)
@ stub GdipTestControl
@ stdcall GdipTransformMatrixPoints(ptr ptr long)
@ stdcall GdipTransformMatrixPointsI(ptr ptr long)
@ stdcall GdipTransformPath(ptr ptr)
@ stdcall GdipTransformPoints(ptr long long ptr long)
@ stdcall GdipTransformPointsI(ptr long long ptr long)
@ stdcall GdipTransformRegion(ptr ptr)
@ stub GdipTranslateClip
@ stub GdipTranslateClipI
@ stub GdipTranslateLineTransform
@ stdcall GdipTranslateMatrix(ptr long long long)
@ stub GdipTranslatePathGradientTransform
@ stub GdipTranslatePenTransform
@ stdcall GdipTranslateRegion(ptr long long)
@ stdcall GdipTranslateRegionI(ptr long long)
@ stub GdipTranslateTextureTransform
@ stdcall GdipTranslateWorldTransform(ptr long long long)
@ stdcall GdipVectorTransformMatrixPoints(ptr ptr long)
@ stdcall GdipVectorTransformMatrixPointsI(ptr ptr long)
@ stub GdipWarpPath
@ stub GdipWidenPath
@ stub GdipWindingModeOutline
@ stub GdiplusNotificationHook
@ stub GdiplusNotificationUnhook
@ stdcall GdiplusShutdown(ptr)
@ stdcall GdiplusStartup(ptr ptr ptr)
