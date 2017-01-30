<?php

/**
 * @file
 * Template for PDFs.
 */

?>

<!DOCTYPE html>
<html lang="en">
<head>
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
  <title><?php print $title; ?></title>
  <?php if ($inline_css): ?>
    <style type="text/css">
      <?php print $inline_css; ?>
    </style>
  <?php endif; ?>
</head>
<body>

<header>
  <div class="logo">
    <?php print $logo; ?>
  </div>
  <div class="header">
    <?php print $invoice_header; ?>
  </div>
</header>

<section class="invoice">
  <div class="pull-right">
    <?php print t('Invoice number:') . ' ' . $invoice_number; ?><br>
    <?php if (isset($order_number)): ?>
      <?php print t('Order number:') . ' ' . $order_number; ?><br>
    <?php endif; ?>
    <?php print t('Invoice date:') . ' ' . $invoice_date; ?><br>
    <?php print t('Invoice due:') . ' ' . $invoice_due; ?><br>
    <?php print t('Status:') . ' ' . $invoice->invoice_status; ?>
  </div>
  <?php print render($content); ?>
</section>

<footer>
  <?php print $invoice_footer; ?>
</footer>

</body>
</html>
