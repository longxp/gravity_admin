<?php

function gravityapp_switch_env($env) {
  dsm($env);
//  drupal_goto('admin/config/gravityapp');
  return '';
}

function gravityapp_switch_dev() {
  $variable_on = variable_get('gravityapp_dev_module_on', '');
  $variable_off = variable_get('gravityapp_dev_module_off', '');
  $delimiter = ",";
  $module_list = explode($delimiter, variable_get('gravityapp_dev_module_on', ''));//lấy list module bật
  $enable = module_enable($module_list);


  //
  try { // nếu có module thì bật và hiện thông báo.
    module_enable($module_list);
    variable_set('annotate_on', $variable_on); //hiện module bật
    drupal_set_message($message = "Enable module", $type = 'status');
  } catch (Exception $q) { // k có thì hiện thông báo
    drupal_set_message($message = "Can't Enable  module", $type = 'warning');
  }

  //lây list module tắt
  $module_list2 = explode($delimiter, variable_get('gravityapp_dev_module_off', ''));
  try {
    module_disable($module_list2); // tắt module
    variable_set('annotate_off', $variable_off); //hiện module tắt
    drupal_set_message($message = "Disable module", $type = 'status', $repeat = TRUE);
  } catch (Exception $e) {
    drupal_set_message($message = "Can't Disable  module", $type = 'warning', $repeat = TRUE);
  }


  /**
   * Xu ly phan tat cache
   * Nut checkbox
   */
  $off_cache =  variable_get('gravityapp_dev_cache_off', "");
  if ($off_cache == 0) {
    variable_set('cache', 0);
  }
  else {
    variable_set('cache', 1);
  }
  /**
   * Xu ly phan tat log
   * Nut checkbox
   */
  $off_log = variable_get('gravityapp_dev_log_off', "");
  if ($off_log == 0) {
    variable_set('block_cache', 0);
  }
  else {
    variable_set('block_cache', 1);
  }
  /**
   * Xu ly phan tat baoloi
   *
   */
  $off_error = variable_get('gravityapp_dev_error_off', "");
  switch ($off_error) {
    case 0:
      variable_set('error_level', 0);
      break;
    case 1:
      variable_set('error_level', 1);
      break;
    case 2:
      variable_set('error_level', 2);
      break;
  }

  /**
   * Xu ly phan tat nen css
   * Nut checkbox
   */
  $tat_css = variable_get('gravityapp_dev_preprocess_css', "");
  if ($tat_css == 0) {
    variable_set('preprocess_css', 0);
  }
  else {
    variable_set('preprocess_css', 1);
  }
  /**
   * Xu ly phan tat nen java
   * Nut checkbox
   */
  $tat_jav = variable_get('gravityapp_dev_preprocess_js', "");
  if ($tat_jav == 0) {
    variable_set('preprocess_js', 0);
  }
  else {
    variable_set('preprocess_js', 1);
  }
  return '';
}
function gravityapp_switch_custom() {
  $variable_on = variable_get('gravityapp_custom_module_on', '');
  $variable_off = variable_get('gravityapp_custom_module_off', '');
  $delimiter = ",";
  $module_list = explode($delimiter, variable_get('gravityapp_custom_module_on', ''));//lấy list module bật
  $enable = module_enable($module_list);


  //
  try { // nếu có module thì bật và hiện thông báo.
    module_enable($module_list);
    variable_set('annotate_on', $variable_on); //hiện module bật
    drupal_set_message($message = "Enable module", $type = 'status');
  } catch (Exception $q) { // k có thì hiện thông báo
    drupal_set_message($message = "Can't Enable  module", $type = 'warning');
  }

  //lây list module tắt
  $module_list2 = explode($delimiter, variable_get('gravityapp_custom_module_off', ''));
  try {
    module_disable($module_list2); // tắt module
    variable_set('annotate_off', $variable_off); //hiện module tắt
    drupal_set_message($message = "Disable module", $type = 'status', $repeat = TRUE);
  } catch (Exception $e) {
    drupal_set_message($message = "Can't Disable  module", $type = 'warning', $repeat = TRUE);
  }


  /**
   * Xu ly phan tat cache
   * Nut checkbox
   */
  $off_cache =  variable_get('gravityapp_custom_cache_off', "");
  if ($off_cache == 0) {
    variable_set('cache', 0);
  }
  else {
    variable_set('cache', 1);
  }
  /**
   * Xu ly phan tat log
   * Nut checkbox
   */
  $off_log = variable_get('gravityapp_custom_log_off', "");
  if ($off_log == 0) {
    variable_set('block_cache', 0);
  }
  else {
    variable_set('block_cache', 1);
  }
  /**
   * Xu ly phan tat baoloi
   *
   */
  $off_error = variable_get('gravityapp_custom_error_off', "");
  switch ($off_error) {
    case 0:
      variable_set('error_level', 0);
      break;
    case 1:
      variable_set('error_level', 1);
      break;
    case 2:
      variable_set('error_level', 2);
      break;
  }

  /**
   * Xu ly phan tat nen css
   * Nut checkbox
   */
  $tat_css = variable_get('gravityapp_custom_preprocess_css', "");
  if ($tat_css == 0) {
    variable_set('preprocess_css', 0);
  }
  else {
    variable_set('preprocess_css', 1);
  }
  /**
   * Xu ly phan tat nen java
   * Nut checkbox
   */
  $tat_jav = variable_get('gravityapp_custom_preprocess_js', "");
  if ($tat_jav == 0) {
    variable_set('preprocess_js', 0);
  }
  else {
    variable_set('preprocess_js', 1);
  }
  return '';
}