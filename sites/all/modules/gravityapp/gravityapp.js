(function ($) {
    Drupal.behaviors.gravityapp = {
        attach: function () { //start code

            $(".vertical-tab-button").click(function(){
                console.log('hehe');
                var $value2 = $(this).find('a').attr('href');
                $("#tab_forcus input").attr('value', $value2 );
            })

        }
    };
})(jQuery);