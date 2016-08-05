<?php

/**
 * Entity Toolbox settings form.
 *
 * @param array $form
 * @param array $form_state
 *
 * @return array
 */
function entity_toolbox_settings_form($form, &$form_state) {

  $form['global']                  = array(
    '#type'  => 'fieldset',
    '#title' => t('Global settings'),
  );
  $form['global']['cache_enabled'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Cache enabled'),
    '#default_value' => variable_get('cache_enabled', FALSE)
  );

  return system_settings_form($form);
}