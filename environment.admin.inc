<?php
// $Id$

/**
 * @file
 * Settings for Environment module
 */

function environment_admin_settings() {
  $form = array();

  $env_override = variable_get('environment_override', NULL);
  if ($env_override) {
    $form['environment'] = array(
      '#type'  => 'item',
      '#title' => t('Current Environment'),
      '#value' => check_plain(variable_get('environment', 'none')),
    );
    $form['environment_override'] = array(
      '#type'  => 'item',
      '#title' => t('Environment Override'),
      '#value' => t('Active'),
    );
  }
  else {
    $form['environment'] = array(
      '#type'          => 'select',
      '#title'         => t('Environment'),
      '#options'       => drupal_map_assoc(array_keys(environment_get())),
      '#default_value' => variable_get('environment', NULL),
    );
  }

  $form['environment_require_override'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Require environment override'),
    '#description'   => t('Used to require that an environment is set in the settings.php file.'),
    '#default_value' => variable_get('environment_require_override', FALSE),
  );

  $form['buttons']['submit'] = array('#type' => 'submit', '#value' => t('Save configuration') );

  return $form;
}

function environment_admin_settings_submit($form, &$form_state) {
  $values = $form_state['values'];

  variable_set('environment_require_override', $values['environment_require_override']);

  $result = environment_switch($values['environment']);
  foreach ($result['messages'] as $message) {
    drupal_set_message(t(check_plain($message)));
  }

  drupal_set_message(t('The configuration options have been saved.'));
}
