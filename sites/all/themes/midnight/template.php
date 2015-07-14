<?php

/**
 * Implements hook_preprocess_html().
 * @param $variables
 */
function midnight_preprocess_html(&$variables) {
  $disable_rss = theme_get_setting('disabling_responsiveness');
  $non_rss_width = theme_get_setting('non_responsive_width');
  if ($disable_rss && $non_rss_width === '1170') {
    $variables['classes_array'][] = 'lg-devices';
  }
}

/**
 * Implements hook_preprocess_page().
 * @param $variables
 */
function midnight_preprocess_page(&$variables) {
  $theme_path = drupal_get_path('theme', 'midnight');
  // These files will be disable responsive feature on theme.
  $disable_rss = theme_get_setting('disabling_responsiveness');
  if ($disable_rss) {
    drupal_add_css($theme_path . '/css/non-responsive.css', array('group' => CSS_THEME));
    drupal_add_js($theme_path . '/js/non-responsive.js', array('group' => JS_THEME));
  }
  else {
    $viewport = array(
      '#tag' => 'meta',
      '#attributes' => array(
        'name' => 'viewport',
        'content' => 'width=device-width, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0',
      ),
    );
    drupal_add_html_head($viewport, 'viewport');
  }

  // Remove default message of system in front page.
  if ($variables['is_front']) {
    // This will remove the 'No front page content has been created yet.'
    hide($variables['page']['content']['system_main']['default_message']);
  }
}

/**
 * Implements hook_preprocess_views_view_grid().
 * @param $variables
 */
function midnight_preprocess_views_view_grid(&$variables) {
  $variables['classes_array'][] = 'table';
  $classes_array = explode(' ', $variables['class']);
  if (!in_array('table', $classes_array)) {
    $classes_array[] = 'table';
  }
  $variables['class'] = implode(' ', $classes_array);
}

/**
 * Overrides theme_pager().
 * @param $variables
 * @throws Exception
 * @return string
 */
function midnight_pager(&$variables) {
  $output = "";
  $items = array();
  $tags = $variables['tags'];
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  $quantity = $variables['quantity'];

  global $pager_page_array, $pager_total;

  // Calculate various markers within this pager piece:
  // Middle is used to "center" pages around the current page.
  $pager_middle = ceil($quantity / 2);
  // Current is the page we are currently paged to.
  $pager_current = $pager_page_array[$element] + 1;
  // First is the first page listed by this pager piece (re quantity).
  $pager_first = $pager_current - $pager_middle + 1;
  // Last is the last page listed by this pager piece (re quantity).
  $pager_last = $pager_current + $quantity - $pager_middle;
  // Max is the maximum page number.
  $pager_max = $pager_total[$element];

  // Prepare for generation loop.
  $i = $pager_first;
  if ($pager_last > $pager_max) {
    // Adjust "center" if at end of query.
    $i = $i + ($pager_max - $pager_last);
    $pager_last = $pager_max;
  }
  if ($i <= 0) {
    // Adjust "center" if at start of query.
    $pager_last = $pager_last + (1 - $i);
    $i = 1;
  }

  // End of generation loop preparation.
  $li_first = theme('pager_first', array(
    'text' => (isset($tags[0]) ? $tags[0] : t('first')),
    'element' => $element,
    'parameters' => $parameters,
  ));
  $li_previous = theme('pager_previous', array(
    'text' => (isset($tags[1]) ? $tags[1] : t('previous')),
    'element' => $element,
    'interval' => 1,
    'parameters' => $parameters,
  ));
  $li_next = theme('pager_next', array(
    'text' => (isset($tags[3]) ? $tags[3] : t('next')),
    'element' => $element,
    'interval' => 1,
    'parameters' => $parameters,
  ));
  $li_last = theme('pager_last', array(
    'text' => (isset($tags[4]) ? $tags[4] : t('last')),
    'element' => $element,
    'parameters' => $parameters,
  ));
  if ($pager_total[$element] > 1) {
    if ($li_first) {
      $items[] = array(
        'class' => array('pager-first'),
        'data' => $li_first,
      );
    }
    if ($li_previous) {
      $items[] = array(
        'class' => array('prev'),
        'data' => $li_previous,
      );
    }
    // When there is more than one page, create the pager list.
    if ($i != $pager_max) {
      if ($i > 1) {
        $items[] = array(
          'class' => array('pager-ellipsis', 'disabled'),
          'data' => '<span>…</span>',
        );
      }
      // Now generate the actual pager piece.
      for (; $i <= $pager_last && $i <= $pager_max; $i++) {
        if ($i < $pager_current) {
          $items[] = array(
            // 'class' => array('pager-item'),
            'data' => theme('pager_previous', array(
              'text' => $i,
              'element' => $element,
              'interval' => ($pager_current - $i),
              'parameters' => $parameters,
            )),
          );
        }
        if ($i == $pager_current) {
          $items[] = array(
            // Add the active class.
            'class' => array('active'),
            'data' => l($i, '#', array('fragment' => '', 'external' => TRUE)),
          );
        }
        if ($i > $pager_current) {
          $items[] = array(
            'data' => theme('pager_next', array(
              'text' => $i,
              'element' => $element,
              'interval' => ($i - $pager_current),
              'parameters' => $parameters,
            )),
          );
        }
      }
      if ($i < $pager_max) {
        $items[] = array(
          'class' => array('pager-ellipsis', 'disabled'),
          'data' => '<span>…</span>',
        );
      }
    }
    // End generation.
    if ($li_next) {
      $items[] = array(
        'class' => array('next'),
        'data' => $li_next,
      );
    }
    if ($li_last) {
      $items[] = array(
        'class' => array('pager-last'),
        'data' => $li_last,
      );
    }
    return '<div class="text-center">' . theme('item_list', array(
      'items' => $items,
      'attributes' => array('class' => array('pagination')),
    )) . '</div>';
  }
  return $output;
}