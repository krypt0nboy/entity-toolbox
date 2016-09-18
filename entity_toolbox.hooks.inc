<?php

/**
 * @file
 * This files contains all the functions used when calling an entity_toolbox hook.
 */

/**
 * Toolbox process and build hooks.
 */

/**
 * Called when processing an entity type toolbox info.
 * Allows other modules to interact with entity_toolbox when processing the info.
 *
 * @param string $entity_type
 *   The entity type name.
 * @param array  $info
 *   The info already processed.
 *
 * @see hook_toolbox_info_process().
 * @see hook_entity_toolbox_entity_get_info().
 * @see hook_entity_toolbox_entity_info().
 */
function _toolbox_info_process($entity_type, &$info) {
  foreach (module_implements('toolbox_info_process') as $module) {
    $function = $module . '_toolbox_info_process';
    $function($entity_type, $info);
  }
}

/**
 * Called when processing an entity type toolbox property info.
 * Allows other modules to interact with entity_toolbox when processing the info.
 *
 * @param string $entity_type
 *   The entity type name.
 * @param array  $info
 *   The info already being processed.
 * @param string $name
 *   The property name.
 *
 * @see hook_toolbox_property_info_process().
 * @see hook_entity_toolbox_entity_get_info().
 * @see hook_entity_toolbox_entity_info().
 */
function _toolbox_property_info_process(&$info, $entity_type, $name) {
  foreach (module_implements('toolbox_property_info_process') as $module) {
    $function = $module . '_toolbox_property_info_process';
    $function($entity_type, $info, $name);
  }
}

/**
 * Clears cache when hook invoked.
 * The hook has to be invoked by a module to be able to clear the cache using this function.
 *
 * @param string $hook
 *   The hook name.
 */
function _toolbox_cache_clear($hook) {
  $hooks = entity_toolbox_cache_hook_get_info($hook);
  if (!empty($hooks)) {
    foreach ($hooks as $cids) {
      $cleared = array();
      foreach ($cids as $cid) {
        //Prevents the same cache cid to be cleared twice.
        if (!in_array($cid, $cleared)) {
          entity_toolbox_cache_clear($cid);
          $cleared[] = $cid;
        }
      }
    }
  }
}

/**
 * Form hooks.
 */

/**
 * Alters a form element before it's attached to the entity form.
 *
 * @param array          $element
 *   The element to alter, passed by reference.
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 * @param string         $name
 *   The property name.
 * @param string         $form_id
 *   The entity form ID.
 * @param null|string    $widget
 *   The field widget type.
 * @param array          $options
 *   An array of options.
 *
 * @see hook_property_element_alter().
 */
function _property_element_alter(&$element, $entity_type, $entity, $name, $form_id, $widget = NULL, $options = array()) {
  //Passing the element to alter to every module implementing the hook.
  foreach (module_implements('property_element_alter') as $module) {
    $function = $module . '_property_element_alter';
    $function($element, $entity_type, $entity, $name, $form_id, $widget, $options);
  }
}

/**
 * Alters the validation of an entity property.
 *
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 * @param string         $name
 *   The property name.
 * @param array          $form
 *   The entity form, passed by reference
 * @param array          $form_state
 *   The form state, passed by reference.
 */
function _property_attach_form_validate($entity_type, $entity, $name, &$form, &$form_state) {
  foreach (module_implements('property_validate') as $module) {
    $function = $module . '_property_validate';
    $function($entity_type, $entity, $name, $form, $form_state);
  }
}

/**
 * Call the alter hooks before returning an entity edit form.
 *
 * @param array          $form
 *   The form to alter, passed by reference.
 * @param array          $form_state
 *   The form_state of the form to alter, passed by reference.
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 *
 * @see hook_type_ENTITY_TYPE_edit_form__alter().
 */
function _entity_edit_form__alter(&$form, &$form_state, $entity_type, $entity) {
  $hook = '_edit_form__alter';
  foreach (entity_toolbox_edit_form_alter_get_info() as $module => $form_alters) {
    if (in_array($entity_type, $form_alters)) {
      $function = $module . '_type_' . $entity_type . $hook;
      $function($form, $form_state, $entity_type, $entity);
    }
  }
}

/**
 * Call the alter hooks before returning an entity delete form.
 *
 * @param array          $form
 *   The form to alter, passed by reference.
 * @param array          $form_state
 *   The form_state of the form to alter, passed by reference.
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 *
 * @see hook_type_ENTITY_TYPE_delete_form__alter().
 */
function _entity_delete_form__alter(&$form, &$form_state, $entity_type, $entity) {
  $hook = '_delete_form__alter';
  foreach (entity_toolbox_delete_form_alter_get_info() as $module => $form_alters) {
    if (in_array($entity_type, $form_alters)) {
      $function = $module . '_type_' . $entity_type . $hook;
      $function($form, $form_state, $entity_type, $entity);
    }
  }
}

/**
 * Call the alter hooks before returning an entity delete form.
 *
 * @param array          $form
 *   The form to alter, passed by reference.
 * @param array          $form_state
 *   The form_state of the form to alter, passed by reference.
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 *
 * @see hook_type_ENTITY_TYPE_inline_entity_form__alter().
 */
function _entity_inline_entity_form__alter(&$form, &$form_state, $entity_type, $entity) {
  $hook = '_inline_entity_form__alter';
  foreach (entity_toolbox_inline_form_alter_get_info() as $module => $form_alters) {
    if (in_array($entity_type, $form_alters)) {
      $function = $module . '_type_' . $entity_type . $hook;
      $function($form, $form_state, $entity_type, $entity);
    }
  }
}

/**
 * Entities hooks.
 */

/**
 * Returns the modules implemented hook_entity_skip_load().
 *
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 *
 * @return array
 *   An array where the values are the module names requesting to skip the load.
 */
function _entity_skip_load($entity_type, $entity) {
  $hook  = '_entity_skip_load';
  $skips = array();

  foreach (entity_toolbox_entity_skip_load_get_info() as $module) {
    $function = $module . $hook;
    $call     = $function($entity_type, $entity);
    if ($call) {
      $skips[] = $call;
    }
  }

  return $skips;
}

/**
 * Alters the validation of an entity property.
 *
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 * @param string         $name
 *   The property name.
 * @param mixed          $value
 *   The property value to validate.
 */
function _property_validate($entity_type, $entity, $name, $value) {
  foreach (module_implements('property_validate') as $module) {
    $function = $module . '_property_validate';
    $function($entity_type, $entity, $name, $value);
  }
}

/**
 * Alters the submit of an entity property.
 *
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 * @param string         $name
 *   The property name.
 * @param array          $form
 *   The entity form, passed by reference
 * @param array          $form_state
 *   The form state, passed by reference.
 */
function _property_submit($entity_type, $entity, $name, &$form, &$form_state) {
  foreach (module_implements('property_submit') as $module) {
    $function = $module . '_property_submit';
    $function($entity_type, $entity, $name, $form, $form_state);
  }
}

/**
 * Returns the modules implementing hook_update_entity_field_settings().
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $bundle
 *   The entity bundle.
 * @param string $name
 *   The field name.
 *
 * @see hook_update_entity_field_settings().
 */
function _update_entity_field_settings($entity_type, $bundle, $name) {
  foreach (module_implements('update_entity_field_settings') as $module) {
    /** @var callable $function */
    $function = $module . '_update_entity_field_settings';
    $function($entity_type, $bundle, $name);
  }
}