$(document).ready(function() {

  // page scroll animation
  $('.page-scoll a').bind('click', function(event) {
        var $anchor = $(this);
        $('html, body').stop().animate({
            scrollTop: ($($anchor.attr('href')).offset().top - 50)
        }, 2250, 'easeInOutExpo');
        event.preventDefault();
  });

});



