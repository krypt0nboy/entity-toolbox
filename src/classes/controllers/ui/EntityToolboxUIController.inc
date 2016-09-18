<?php

/**
 * @file
 *
 * This file contains default entity toolbox entity UI controller classes.
 */

/**
 * Class EntityToolboxUIController
 *
 * This class is based on \EntityDefaultUIController.
 * Either \EntityToolboxFieldableUIController or \EntityToolboxNotFieldableUIController should be implemented in code.
 */
class EntityToolboxUIController extends EntityDefaultUIController {

  /** @var  array $toolboxInfo */
  protected $toolboxInfo;
  /** @var string $wildcard */
  protected $wildcard;
  /** @var  string[] $formSettings */
  protected $formSettings;
  /** @var  string[] $formsIds */
  protected $formsIds;
  /** @var  string $basePath */
  protected $basePath;

  /**
   * EntityToolboxUIController constructor.
   *
   * @param string $entity_type
   *   The entity type. * Entity Toolbox provides
   * @param array  $entity_info
   *   The entity info passed by entity_get_info().
   *
   * @see entity_get_info().
   */
  public function __construct($entity_type, $entity_info) {
    parent::__construct($entity_type, $entity_info);
    $this->path     = entity_get_path($this->entityType, 'admin');
    $this->id_count = count(explode('/', $this->path));
    $this->wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : "%$this->entityInfo";
    $this->setFormsIds();
  }

  /**
   * Returns the entity type single label.
   *
   * @return string
   */
  public function labelSingle() {
    return $this->toolboxInfo['labels']['single'];
  }

  /**
   * Returns the entity type single label.
   *
   * @return string
   */
  public function labelPlural() {
    return $this->toolboxInfo['labels']['plural'];
  }

  /**
   * Returns the admin ui wildcard.
   *
   * @return string
   */
  public function wildcard() {
    return $this->wildcard;
  }

  /**
   * Returns the content for the entity add page.
   *
   * @return mixed
   */
  public function addPage() {
    $item    = menu_get_item();
    $content = system_admin_menu_block($item);
    if (count($content) == 1) {
      $item = array_shift($content);
      drupal_goto($item['href']);
    }

    return theme('entity_add_list', array(
      'type'    => $this->entityType,
      'content' => $content,
    ));
  }

  /**
   * Sets the entity forms IDs.
   */
  public function setFormsIds() {
    //@todo replace with iteration over form types.
    $this->formsIds = array(
      'edit'   => $this->entityType . '_edit_form',
      'delete' => $this->entityType . '_delete_form',
    );
  }

  /**
   * Returns the entity edit form ID.
   *
   * @return string
   */
  public function editFormId() {
    return $this->formsIds['edit'];
  }

  /**
   * Returns the entity delete form ID.
   *
   * @return string
   */
  public function deleteFormId() {
    return $this->formsIds['delete'];
  }

  /**
   * Returns the default entity forms settings.
   *
   * @return array
   */
  public function formDefaultSettings() {
    return array(
      'ajax_enabled'  => variable_get('ajax_enabled'),
      'notifications' => variable_get('notifications_enabled'),
    );
  }

  /**
   * Updates the entity forms settings.
   *
   * @param \EntityToolbox $entity
   *   The entity.
   * @param string[]       $options
   *   The options passed to the form.
   */
  public function updateFormSettings($entity, $options = array()) {
    $this->formSettings['ajax_enabled'] = !$entity->is_new;
  }

  /**
   * Builds the entity root menu item.
   *
   * @return mixed
   */
  public function rootMenuItemBuild() {
    $label_plural      = $this->labelPlural();
    $item[$this->path] = array(
      'title'            => $label_plural,
      'type'             => MENU_LOCAL_TASK,
      'description'      => "Add, edit and update $label_plural.",
      'page callback'    => 'system_admin_menu_block_page',
      //@TODO : replace access arguments with actual access arguments for an entity type.
      'access arguments' => array('access administration pages'),
      'file path'        => drupal_get_path('module', 'system'),
      'file'             => 'system.admin.inc',
    );

    return $item;
  }

  /**
   * Builds the a menu item for a given action type.
   *
   * @param string $action
   *   The action type for which to build the menu item.
   *
   * @see hook_toolbox_action_type_info().
   * @see entity_toolbox_entity_action_type_get_info().
   *
   */
  public function actionTypeMenuItemBuild($action) {

  }

  /**
   * {@inheritdoc}
   *
   * @see EntityDefaultUIController::hook_forms().
   */
  public function hook_forms() {
    $forms                                     = array();
    $forms[$this->entityType . '_edit_form']   = array(
      'callback'         => 'entity_toolbox_ui_edit_form',
      'wrapper_callback' => '',
    );
    $forms[$this->entityType . '_delete_form'] = array(
      'callback'         => 'entity_toolbox_ui_delete_form',
      'wrapper_callback' => '',
    );
    $forms += parent::hook_forms();

    return $forms;
  }

  /**
   * Allows to wrap an entity form.
   *
   * @param \EntityToolbox $entity
   *   The entity.
   * @param array          $form
   *   The entity form, passed by reference.
   * @param array          $form_state
   *   The form state, passed by reference.
   */
  public function entityFormWrap($entity, &$form, &$form_state) {
    $wrappers = array();
    //@todo add hook_entity_form_wrap($entity_type, $entity, $form, $form_state, &$wraps)
  }

  /**
   * Builds the entity edit_form.
   *
   * @param array          $form
   *   The entity form built by drupal_get_form.
   * @param array          $form_state
   *   The form_state generated by drupal_get_form.
   * @param \EntityToolbox $entity
   *   The entity to be edited.
   * @param array          $options
   *   The form options.
   *
   * @return array
   */
  public function entityEditForm($form, &$form_state, $entity, $options = array()) {
    $this->updateFormSettings($entity, $options);
    $form_state['entity_type'] = $this->entityType;
    $form_state['#entity']     = $entity;
    $form_state['#options']    = $this->formDefaultSettings() + $options;
    $this->entityFormWrap($entity, $form, $form_state);

    return $form;
  }

  /**
   * Validation callback for the entity form.
   *
   * @param $form
   *   The form to validate.
   * @param $form_state
   *   The form state.
   */
  public function entityEditFormValidate($form, &$form_state) {
    //TODO : add hook_entity_edit_form_validate().
    $entity = $form_state[$this->entityType];
    properties_attach_form_validate($this->entityType, $entity, $form, $form_state);
    field_attach_form_validate($this->entityType, $entity, $form, $form_state);
  }

  /**
   * Submit callback for the entity form.
   *
   * @param $form
   *   The form to submit, passed by reference.
   * @param $form_state
   *   The form state.
   */
  public function entityEditFormSubmit(&$form, &$form_state) {
    //TODO : add hook_entity_edit_form_submit().
    $entity = $form_state[$this->entityType];
    properties_attach_form_submit($this->entityType, $entity, $form, $form_state);
  }

  /**
   * Builds the entity delete_form.
   *
   * @param array          $form
   *   The entity form built by drupal_get_form.
   * @param array          $form_state
   *   The form_state generated by drupal_get_form.
   * @param \EntityToolbox $entity
   *   The entity to be deleted.
   * @param string[]       $options
   *   The form options.
   *
   * @return array
   */
  public function entityDeleteForm($form, &$form_state, $entity, $options = array()) {
    $this->updateFormSettings($entity, $options);
    $form_state['entity_type'] = $this->entityType;
    $form_state['#entity']     = $entity;
    $form_state['#options']    = $this->formDefaultSettings() + $options;
    $this->entityFormWrap($entity, $form, $form_state);
  }

  /**
   * Validates the entity delete_form.
   *
   * @param array $form
   *   The entity delete form to validate.
   * @param array $form_state
   *   The form state, passed by reference.
   */
  public function entityDeleteFormValidate($form, &$form_state) {

  }

  /**
   * Submits the entity delete_form.
   *
   * @param array $form
   *   The entity delete form to submit, passed by reference.
   * @param array $form_state
   *   The form state, passed by reference.
   */
  public function entityDeleteFormSubmit(&$form, &$form_state) {
    $entity_type = $this->entityType;
    /** @var \EntityToolbox $entity */
    $entity = $form_state['#entity'];
    entity_delete($entity_type, entity_id($entity_type, $entity));
    drupal_set_message(t('The %entity_label %name has been deleted.', array(
      '%name'         => $entity->label(),
      '%entity_label' => $this->labelSingle(),
    )));
    watchdog(entity_type_single2plural($entity_type), 'Deleted %entity_label %name.', array(
      '%name'         => $entity->label(),
      '%entity_label' => $this->labelSingle(),
    ));

    $form_state['redirect'] = entity_get_path($entity_type, 'admin');
  }

}