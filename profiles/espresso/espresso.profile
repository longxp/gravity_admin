<?php
/**
 * @file
 * Enables modules and site configuration for a standard site installation.
 */

/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form().
 *
 * Allows the profile to alter the site configuration form.
 * @param $form
 * @param $form_state
 */
function espresso_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value'] = st('Espresso Café');

  // Pre-populate the site email address.
  $form['site_information']['site_mail']['#default_value'] = 'info@gravitybrand.vn';

  // Pre-populate the administrator account details.
  $form['admin_account']['account']['name']['#default_value'] = 'admin';

  // Configure "Server settings" fieldset collapsed in default.
  $form['server_settings']['#collapsible'] = TRUE;
  $form['server_settings']['#collapsed'] = TRUE;

  // Configure "Update notifications" fieldset collapsed in default.
  $form['update_notifications']['#collapsible'] = TRUE;
  $form['update_notifications']['#collapsed'] = TRUE;

  // Pre-populate turn off receive e-mail notifications.
  $form['update_notifications']['update_status_module']['2']['#default_value'] = '0';
}
