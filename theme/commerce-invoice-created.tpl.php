<?php

/**
 * @file
 */
?>
<?php if ($created): ?>
  <div class="commerce-invoice-created">
    <?php if ($label): ?>
    <div class="commerce-invoice-created-label">
      <?php print $label; ?>
    </div>
    <?php endif; ?>
    <?php print $created; ?>
  </div>
<?php endif; ?>
