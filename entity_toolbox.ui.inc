<?php

/**
 * @file
 *
 * This file contains the functions required by \EntityToolboxUIController.
 *
 * @see \EntityToolboxFieldableUIController
 * @see \EntityToolboxNotFieldableUIController
 */

/**
 * Return the toolbox ui controller for a entity type.
 *
 * @param $entity_type
 *   The entity type.
 *
 * @return \EntityToolboxUIController
 */
function entity_toolbox_ui_controller($entity_type) {
  if (in_array($entity_type, entity_toolbox_entity_get_info())) {
    return entity_ui_controller($entity_type);
  }
}

/**
 * Returns the entity type add page content.
 *
 * @param $entity_type
 *   The entity type.
 *
 * @return mixed
 */
function entity_toolbox_ui_add_page($entity_type) {
  return entity_toolbox_ui_controller($entity_type)->addPage();
}

/**
 * Returns an entity edit form.
 *
 * @param       $form
 *   The form build by drupal_get_form().
 * @param       $form_state
 *   The form state, passed by reference.
 * @param       $entity
 *   The entity to edit.
 * @param       $entity_type
 *   The entity type.
 * @param array $options
 *   The form options.
 *
 * @return array
 */
function entity_toolbox_ui_edit_form($form, &$form_state, $entity, $entity_type, $options = array()) {
  return entity_toolbox_ui_controller($entity_type)->entityEditForm($form, $form_state, $entity, $options);
}

/**
 * Validates an entity edit form.
 *
 * @param array  $form
 *   The entity form.
 * @param array  $form_state
 *   The form state, passed by reference.
 * @param string $entity_type
 *   The entity type.
 */
function entity_toolbox_edit_form_validate($form, &$form_state, $entity_type) {
  entity_toolbox_ui_controller($entity_type)->entityEditFormValidate($form, $form_state);
}

/**
 * Submits an entity edit form.
 *
 * @param array  $form
 *   The entity form, passed by reference.
 * @param array  $form_state
 *   The form state, passed by reference.
 * @param string $entity_type
 *   The entity type.
 */
function entity_toolbox_edit_form_submit(&$form, &$form_state, $entity_type) {
  entity_toolbox_ui_controller($entity_type)->entityEditFormSubmit($form, $form_state);
}

/**
 * Returns an entity delete form.
 *
 * @param       $form
 *   The form build by drupal_get_form().
 * @param       $form_state
 *   The form state, passed by reference.
 * @param       $entity
 *   The entity to delete.
 * @param       $entity_type
 *   The entity type.
 * @param array $options
 *   The form options.
 *
 * @return array
 */
function entity_toolbox_ui_delete_form($form, &$form_state, $entity, $entity_type, $options = array()) {
  return entity_toolbox_ui_controller($entity_type)->entityDeleteForm($form, $form_state, $entity, $options);
}

/**
 * Validates an entity delete form.
 *
 * @param array  $form
 *   The entity delete form to validate.
 * @param array  $form_state
 *   The form state, passed by reference.
 * @param string $entity_type
 *   The entity type.
 */
function entity_toolbox_delete_form_validate($form, &$form_state, $entity_type) {
  entity_toolbox_ui_controller($entity_type)->entityDeleteFormValidate($form, $form_state);
}

/**
 * Submits an entity delete form.
 *
 * @param array  $form
 *   The entity delete form to validate, passed by reference.
 * @param array  $form_state
 *   The form state, passed by reference.
 * @param string $entity_type
 *   The entity type.
 */
function entity_toolbox_delete_form_submit(&$form, &$form_state, $entity_type) {
  entity_toolbox_ui_controller($entity_type)->entityDeleteFormSubmit($form, $form_state);
}

/**
 * Returns the default options for an entity form.
 *
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 * @param string         $form_id
 *   The entity form ID.
 *
 * @return array
 */
function entity_get_form_updated_settings($entity_type, $entity, $form_id) {
  return entity_toolbox_ui_controller($entity_type)->updateFormSettings($entity);
}