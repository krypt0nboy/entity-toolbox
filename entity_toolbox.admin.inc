<?php

/**
 * Entity Toolbox settings form.
 *
 * @param array $form
 *   The form built by drupal_get_form().
 * @param array $form_state
 *   The form state, passed by reference.
 *
 * @return array
 */
function entity_toolbox_settings_form($form, &$form_state) {
  $form['global']                            = array(
    '#type'  => 'fieldset',
    '#title' => t('Global settings'),
  );
  $form['global']['cache_enabled']           = array(
    '#type'          => 'checkbox',
    '#title'         => t('Cache enabled'),
    '#default_value' => variable_get('cache_enabled', FALSE)
  );
  $form['global']['ajax_enabled']            = array(
    '#type'          => 'checkbox',
    '#title'         => t('Ajax enabled'),
    '#default_value' => variable_get('ajax_enabled', TRUE)
  );
  $form['global']['notifications_enabled']   = array(
    '#type'          => 'checkbox',
    '#title'         => t('Notifications enabled'),
    '#default_value' => variable_get('notifications_enabled', TRUE)
  );
  $form['properties']                        = array(
    '#type'  => 'fieldset',
    '#title' => t('Properties settings'),
  );
  $form['properties']['default_precision']   = array(
    '#type'          => 'textfield',
    '#title'         => t('Default precision for DecimalProperty'),
    '#default_value' => variable_get('default_precision', 10)
  );
  $form['properties']['default_scale']       = array(
    '#type'          => 'textfield',
    '#title'         => t('Default scale for DecimalProperty'),
    '#default_value' => variable_get('default_scale', 2)
  );

  return system_settings_form($form);
}