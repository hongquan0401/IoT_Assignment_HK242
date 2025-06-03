function doPost(e) {
  const sheetData =
    SpreadsheetApp.getActiveSpreadsheet().getSheetByName("AccessLog");
  const logSheet = SpreadsheetApp.getActiveSpreadsheet().getSheetByName("Log");
  const data = JSON.parse(e.postData.contents);
  const uid = data.uid.toUpperCase();

  const rows = sheetData.getDataRange().getValues();

  for (let i = 1; i < rows.length; i++) {
    if (rows[i][0] == uid) {
      const name = rows[i][1];
      const timestamp = new Date();
      logSheet.appendRow([timestamp, uid, name]);

      return ContentService.createTextOutput(
        JSON.stringify({
          status: "allowed",
          name: name,
        })
      ).setMimeType(ContentService.MimeType.JSON);
    }
  }

  return ContentService.createTextOutput(
    JSON.stringify({
      status: "denied",
    })
  ).setMimeType(ContentService.MimeType.JSON);
}
