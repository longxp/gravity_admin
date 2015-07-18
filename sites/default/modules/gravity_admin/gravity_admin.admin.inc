<?php

/**
 * @file
 * Admin page callbacks for the system module.
 */

/**
 * Menu callback; Provide the administration overview page.
 */

/**
* Implements hook_form()
* Customize Configuration form
*/
function gravity_admin_config_form($form, &$form_state){
    $form = array();

    $form['site_title'] = array(
        '#type' => 'textfield',
        '#title' => 'Site Title: ',
        '#default_value' => variable_get('site_name', 'Drupal'),
        '#required' => TRUE,
    );
    $form['slogan'] = array(
        '#type' => 'textfield',
        '#title' => 'Slogan: ',
        '#default_value' => variable_get('site_slogan', ''),
    );
    $form['email'] = array(
        '#type' => 'textfield',
        '#title' => 'E-mail Address: ',
        '#default_value' => variable_get('site_mail', ini_get('sendmail_from')),
        '#required' => TRUE,
    );
    $form['front_page'] = array(
        '#type' => 'textfield',
        '#title' => 'Default front page: ',
        '#default_value' => (variable_get('site_frontpage')!='node'?drupal_get_path_alias(variable_get('site_frontpage', 'node')):''),
        '#size' => 50,
        '#field_prefix' => url(NULL, array('absolute' => TRUE)) . (variable_get('clean_url', 0) ? '' : '?q='),
    );
    $form['member'] = array(
        '#type' => 'radios',
        '#title' => 'Who can register accounts?',
        '#default_value' => variable_get('user_register', USER_REGISTER_VISITORS_ADMINISTRATIVE_APPROVAL),
        '#options' => array(
            USER_REGISTER_ADMINISTRATORS_ONLY => t('Administrators only'),
            USER_REGISTER_VISITORS => t('Visitors'),
            USER_REGISTER_VISITORS_ADMINISTRATIVE_APPROVAL => t('Visitors, but administrator approval is required'),
        )
    );
    $form['time_zone'] = array(
        '#type' => 'select',
        '#title' => 'Time Zone: ',
        '#default_value' => variable_get('date_default_timezone', date_default_timezone_get()),
        '#options' => system_time_zones(),
    );
    $form['date_first_day'] = array(
        '#type' => 'select',
        '#title' => 'First day of week',
        '#default_value' => variable_get('date_first_day', 0),
        '#options' => array(0 => t('Sunday'), 1 => t('Monday'), 2 => t('Tuesday'), 3 => t('Wednesday'), 4 => t('Thursday'), 5 => t('Friday'), 6 => t('Saturday')),
    );
    $form['submit_button'] = array(
        '#type' => 'submit',
        '#value' => t('Save config'),
    );
    $form['#validate'][] = 'gravity_admin_config_validate';

    return $form;
}

/**
 * Validates the submitted configuration form.
 */

function gravity_admin_config_validate($form, &$form_state) {
    // Validate the e-mail address.
    if ($error = user_validate_mail($form_state['values']['email'])) {
        form_set_error('email', $error);
    }
}

function gravity_admin_config_form_submit($form, &$form_state) {
    //dsm($form_state);
    variable_set('site_name', $form_state['values']['site_title']);
    variable_set('site_slogan', $form_state['values']['slogan']);
    variable_set('site_mail', $form_state['values']['email']);
    variable_set('user_register', $form_state['values']['member']);
    variable_set('date_default_timezone', $form_state['values']['time_zone']);
    variable_set('date_first_day', $form_state['values']['date_first_day']);
}
