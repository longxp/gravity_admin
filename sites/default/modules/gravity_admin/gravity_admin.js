(function ($) {
    Drupal.behaviors.gravity_admin = {
        attach: function () { //start code
            var $root = $('body');

            var $payment_content = $('#block-views-payment-tab-block');
            var a1 = $payment_content.clone();
            $("#payment-content").html(a1);




        }//code ends
    };
})(jQuery);