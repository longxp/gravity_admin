<?php

/**
 * @file
 * Contains Batch API callbacks used during installation.
 */

/**
 * BatchAPI callback.
 * @see commerce_kickstart_install_additional_modules()
 * @param $module
 * @param $module_name
 * @param $context
 */
function _espresso_operation_enable_module($module, $module_name, &$context) {
  module_enable(array($module), FALSE);
  $context['message'] = st('Installed %module module.', array('%module' => $module_name));
}

/**
 * Batch operation - Configure variables of website.
 * @param $context
 */
function _espresso_operation_configure_variable(&$context) {
  $context['message'] = st('Configuring variables');
  variable_set('error_level', 1);

  if (module_exists('jquery_update')) {
    variable_set('jquery_update_compression_type', 'min');
    variable_set('jquery_update_jquery_admin_version', '1.7');
    variable_set('jquery_update_jquery_cdn', 'none');
    variable_set('jquery_update_jquery_version', '1.9');
  }

  if (module_exists('module_filter')) {
    variable_set('module_filter_track_recent_modules', 0);
  }

  if (module_exists('pathauto')) {
    variable_set('pathauto_transliterate', 1);
  }

  if (module_exists('views_ui')) {
    variable_set('views_ui_show_advanced_help_warning', 0);
  }
}

/**
 * Batch operation - Create a Backup and Migrate profile.
 * @param $context
 */
function _espresso_operation_create_backup_migrate_profile(&$context) {
  $context['message'] = st('Creating Backup and Migrate profile');

  $machine_name = 'default';
  $result = db_query('SELECT bmp.profile_id, bmp.machine_name, bmp.name, bmp.filters ' .
    'FROM {backup_migrate_profiles} bmp ' .
    'WHERE bmp.machine_name = :machine_name', array(':machine_name' => $machine_name));
  if ($result->rowCount() == 0) {
    module_load_include('inc', 'backup_migrate', 'includes/profiles');
    $params = array('name' => t('Default Settings'), 'machine_name' => $machine_name);
    $profile = new backup_migrate_profile;
    $profile = $profile->create($params);
    $profile->filters['compression'] = 'zip';
    $profile->save();
  }
}

/**
 * Batch operation - Configure module Backup and Migrate.
 * @param $context
 */
function _espresso_operation_configure_backup_migrate(&$context) {
  $context['message'] = st('Configuring Backup and Migrate profile');

  $machine_name = 'default';
  $result = db_query('SELECT bmp.profile_id, bmp.machine_name, bmp.name, bmp.filters ' .
    'FROM {backup_migrate_profiles} bmp ' .
    'WHERE bmp.machine_name = :machine_name', array(':machine_name' => $machine_name));
  if ($result->rowCount() == 0) {
    module_load_include('inc', 'backup_migrate', 'includes/crud');
    $params = array('name' => t('Default Settings'), 'machine_name' => $machine_name);
    $profile = backup_migrate_crud_create_item('profile', $params);

    $maintenance_mode_message = variable_get('maintenance_mode_message',
      t('@site is currently under maintenance. We should be back shortly. Thank you for your patience.',
        array('@site' => variable_get('site_name', 'Drupal'))));
    $filters = $profile->filters;
    $nodata_tables = $filters['sources']['db']['nodata_tables'];
    $exists_tables = array();
    foreach ($nodata_tables as $table) {
      if (db_table_exists($table)) {
        $exists_tables[$table] = $table;
      }
    }
    ksort($exists_tables);

    $profile->filters = array(
      'compression' => 'zip',
      'notify_success_enable' => ($filters['notify_success_enable']) ? 1 : 0,
      'notify_success_email' => $filters['notify_success_email'],
      'notify_failure_enable' => ($filters['notify_failure_enable']) ? 1 : 0,
      'notify_failure_email' => $filters['notify_failure_email'],
      'utils_site_offline' => ($filters['utils_site_offline']) ? 1 : 0,
      'utils_site_offline_message' => $maintenance_mode_message,
      'utils_description' => $filters['utils_description'],
      'use_cli' => 0,
      'ignore_errors' => 0,
      'sources' => array(
        'db' => array(
          'exclude_tables' => $filters['sources']['db']['exclude_tables'],
          'nodata_tables' => array_merge($exists_tables, $nodata_tables),
          'utils_lock_tables' => ($filters['sources']['db']['utils_lock_tables']) ? 1 : 0,
        ),
        'files' => $filters['sources']['files'],
        'archive' => $filters['sources']['archive'],
      ),
    );
    $profile->save();
  }
}

/**
 * Batch operation - Rebuild theme settings.
 * @param $context
 */
function _espresso_operation_rebuild_theme(&$context) {
  $context['message'] = st('Rebuilding theme and system settings');
  _system_rebuild_theme_data();
}

/**
 * Batch operation - Rebuild Cache.
 * @param $context
 */
function _espresso_operation_flush_cache(&$context) {
  $context['message'] = st('Rebuilding cache');
  drupal_flush_all_caches();

  // Cache a fully-built schema.
  drupal_get_schema(NULL, TRUE);
}

/**
 * Batch operation - Clear all recent log messages.
 * @param $context
 */
function _espresso_operation_clear_watchdog(&$context) {
  $context['message'] = st('Removing log messages');
  db_truncate('watchdog')->execute();
}

