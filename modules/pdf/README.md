# Commerce Invoice PDF

Creates PDFs for invoices.

## Installation

1. Set up the private filesystem in `admin/config/media/file-system`

2. Download the DOMPDF library and place it in the libraries folder,
  e.g. `sites/all/libraries/dompdf`
   
  Example drush make config:

      libraries[dompdf][download][type] = "get"
      libraries[dompdf][download][url] = "https://github.com/dompdf/dompdf/releases/download/v0.6.2/dompdf-0.6.2.zip"
   
3. Add DOMPDF fonts to the public filesystem.

  Copy `libraries/dompdf/lib/fonts` to your public files directory under
  `public://fonts` (example: `sites/default/files/fonts`).
