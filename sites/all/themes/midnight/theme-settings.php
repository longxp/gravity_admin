<?php

/**
 * Implements hook_form_FORM_ID_alter().
 * @param $form
 * @param $form_state
 */
function midnight_form_system_theme_settings_alter(&$form, &$form_state) {
  // Disabling responsiveness
  $form['advanced']['responsive_utilities'] = array(
    '#type' => 'fieldset',
    '#title' => t('Responsive utilities'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['advanced']['responsive_utilities']['disabling_responsiveness'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disabling responsiveness'),
    '#default_value' => theme_get_setting('disabling_responsiveness'),
    '#description' => t('Enable this if you want to disabling responsiveness on theme.'),
  );
  $form['advanced']['responsive_utilities']['non_responsive_width'] = array(
    '#type' => 'select',
    '#title' => t('Default container width'),
    '#description' => t('Select your default width of container class on page.'),
    '#default_value' => theme_get_setting('non_responsive_width'),
    '#options' => array(
      '970' => t('Medium devices (970px)'),
      '1170' => t('Large devices (1170px)'),
    ),
    '#states' => array(
      'invisible' => array(
        ':input[name="disabling_responsiveness"]' => array('checked' => FALSE),
      ),
    ),
  );
}
