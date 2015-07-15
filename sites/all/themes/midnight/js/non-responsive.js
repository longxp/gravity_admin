+function($) {
    'use strict';
    // Disabling responsiveness
    $(window).on('load', function() {
        for (var $i = 1; $i < 13; $i++) {
            var $xs_class = 'col-xs-' + $i, $sm_class = 'col-sm-' + $i;
            var $md_class = 'col-md-' + $i, $lg_class = 'col-lg-' + $i;
            // find add elements have class "col-sm-*", remove it and add class "col-xs-*";
            $('.' + $sm_class).each(function() {
                if ($(this).length > 0) {
                    $(this).addClass($xs_class).removeClass($sm_class);
                }
            });
            // find add elements have class "col-md-*", remove it and add class "col-xs-*";
            $('.' + $md_class).each(function() {
                if ($(this).length > 0) {
                    $(this).addClass($xs_class).removeClass($md_class);
                }
            });
            // find add elements have class "col-lg-*", remove it and add class "col-xs-*";
            $('.' + $lg_class).each(function() {
                if ($(this).length > 0) {
                    $(this).addClass($xs_class).removeClass($lg_class);
                }
            });
        }
    });
}(jQuery);