<?php

/**
 * @file
 * Template for PDFs.
 */

?>

<!DOCTYPE html>
<html lang="en">
<head>
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
  <title><?php print $title; ?></title>
  <?php if ($inline_css): ?>
  <style type="text/css">
    <?php print $inline_css; ?>
  </style>
  <?php endif; ?>
</head>
<body>

<header class="header">
  <?php print $logo; ?>
</header>

<section class="invoice">
  <?php print render($invoice); ?>
</section>

</body>
</html>
