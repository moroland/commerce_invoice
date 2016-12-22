(function ($) {
    Drupal.behaviors.invoiceFieldsetSummaries = {
        attach: function (context) {
            $('fieldset#edit-user', context).drupalSetSummary(function (context) {
                var name = $('#edit-owner').val() || Drupal.settings.anonymous;
                return Drupal.t('Owned by @name', {'@name': name});
            });
        }
    };
})(jQuery);
