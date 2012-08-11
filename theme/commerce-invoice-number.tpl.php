<?php

/**
 * @file
 */
?>
<?php if ($invoice_number): ?>
  <div class="commerce-invoice-number">
    <?php if ($label): ?>
      <div class="commerce-invoice-number-label">
        <?php print $label; ?>
      </div>
    <?php endif; ?>
    <?php print $invoice_number; ?>
  </div>
<?php endif; ?>
