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

/**
 * Class EntityToolboxFieldableUIController
 *
 * The default UI Controller for fieldable entities.
 */
class EntityToolboxFieldableUIController extends EntityToolboxUIController {

  /**
   *{@inheritdoc}
   */
  public function entityEditForm($form, &$form_state, $entity, $options = array()) {
    $form += parent::entityEditForm($form, $form_state, $entity, $options);
    //Attach the entity properties to the form.
    properties_attach_form($this->entityType, $entity, $form, $form_state);
    //Attach the entity fields to the form.
    field_attach_form($this->entityType, $entity, $form, $form_state);

    $form['actions'] = array(
      '#type'       => 'container',
      '#attributes' => array('class' => array('form-actions')),
      '#weight'     => 400,
    );
    $submit          = array();
    if (!empty($form['#submit'])) {
      $submit += $form['#submit'];
    }
    $form['actions']['submit'] = array(
      '#type'   => 'submit',
      '#value'  => t('Save'),
      '#submit' => $submit + array('entity_toolbox_ui_edit_form_submit'),
    );
    if (!empty($entity->name)) {
      $form['actions']['delete'] = array(
        '#type'   => 'submit',
        '#value'  => t('Delete'),
        '#suffix' => l(t('Cancel'), entity_get_path($this->entityType, 'admin')),
        '#submit' => $submit + array('entity_toolbox_form_submit_delete'),
        '#weight' => 45,
      );
    }
    $form['#validate'][] = 'entity_toolbox_ui_edit_form_validate';

    //Let other modules alter the form.
    _entity_edit_form__alter($form, $form_state, $this->entityType, $entity);

    return $form;
  }

  /**
   * {@inheritdoc}
   */
  public function entityEditFormValidate($form, &$form_state) {
    parent::entityEditFormValidate($form, $form_state);
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
    parent::entityEditFormSubmit($form, $form_state);
    $entity = $form_state[$this->entityType];
    field_attach_submit($this->entityType, $entity, $form, $form_state);
  }

  /**
   * Builds the entity delete_form.
   *
   * @param array  $form
   *   The entity form built by drupal_get_form.
   * @param array  $form_state
   *   The form_state generated by drupal_get_form.
   * @param object $entity
   *   The entity to be deleted.
   * @param array  $options
   *   The form options.
   *
   * @return array
   */
  public function entityDeleteForm($form, &$form_state, $entity, $options = array()) {
    $form_state['entity_type']     = $this->entityType;
    $form_state[$this->entityType] = $entity;

    $form_state['#options'] = $options;
    $form['#submit'][]      = 'entity_toolbox_delete_form_submit';
    $form                   = confirm_form(
      $form,
      t('Are you sure you want to delete %entity_label %name?', array(
        '%entity_label' => $this->toolboxInfo(),
        '%name'         => $entity->name
      )),
      entity_get_path($this->entityType, 'manage'),
      '<p>' . t('This action cannot be undone.') . '</p>',
      t('Delete'),
      t('Cancel'),
      'confirm'
    );
  }

  /**
   * {@inheritdoc}
   **/
  public function entityDeleteFormValidate($form, &$form_state) {
    parent::entityDeleteFormValidate($form, $form_state);
  }

  /**
   * {@inheritdoc}
   **/
  public function entityDeleteFormSubmit(&$form, &$form_state) {
    parent::entityDeleteFormSubmit($form, $form_state);
  }

  /**
   * Provides the menu items for hook_menu().
   *
   * @see hook_menu().
   */
  public function hook_menu() {
    $items           = array();
    $id_count        = $this->id_count;
    $label           = $this->labelSingle();
    $create_callback = $this->toolboxInfo['callbacks']['create'];
    $access_callback = $this->toolboxInfo['callbacks']['access'];
    $page_callback   = $this->toolboxInfo['callbacks']['page'];
    $title_callback  = $this->toolboxInfo['callbacks']['title'];
    $wildcard        = $this->wildcard();
    $items += $this->rootMenuItemBuild();

    $items[$this->path . '/add'] = array(
      'title'            => "Add a $label",
      'description'      => "Add a new $label.",
      'page callback'    => 'entity_toolbox_ui_add_page',
      'page arguments'   => array($this->entityType),
      'access callback'  => $access_callback,
      'access arguments' => array('edit'),
      'type'             => MENU_NORMAL_ITEM,
      'weight'           => 20,
      'file'             => 'entity_toolbox.entities.functions.inc',
      'file path'        => ENTITY_TOOLBOX_PATH,
    );
    foreach (entity_get_types($this->entityType) as $type) {
      $items[$this->path . '/add/' . $type->type] = array(
        'title'            => "Add $type->label",
        'page callback'    => 'entity_toolbox_ui_edit_form',
        'page arguments'   => array($create_callback(array('type' => $type->type))),
        'access callback'  => $access_callback,
        'access arguments' => array('edit', 'edit ' . $type->type),
        'file'             => 'entity_toolbox.entities.functions.inc',
        'file path'        => ENTITY_TOOLBOX_PATH,
      );
    }
    $items[$this->entityType . '/' . $wildcard]             = array(
      'page callback'    => 'entity_toolbox_ui_edit_form',
      'page arguments'   => array($id_count + 1),
      'access callback'  => $access_callback,
      'access arguments' => array('edit', $id_count + 1),
      'weight'           => 0,
      'context'          => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
      'file'             => 'entity_toolbox.entities.functions.inc',
      'file path'        => ENTITY_TOOLBOX_PATH,
    );
    $items[$this->entityType . '/' . $wildcard . '/edit']   = array(
      'title'   => 'Edit',
      'type'    => MENU_DEFAULT_LOCAL_TASK,
      'weight'  => -10,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
    );
    $items[$this->entityType . '/' . $wildcard . '/view']   = array(
      'title'            => "View",
      'weight'           => -10,
      'page callback'    => $page_callback,
      'page arguments'   => array($id_count + 1),
      'access callback'  => $access_callback,
      'access arguments' => array('view', $id_count + 1),
      'type'             => MENU_LOCAL_TASK,
    );
    $items[$this->entityType . '/' . $wildcard . '/delete'] = array(
      'title'            => "Delete",
      'page callback'    => 'entity_toolbox_ui_delete_form',
      'page arguments'   => array($id_count + 1),
      'access callback'  => $access_callback,
      'access arguments' => array('edit', $id_count + 1),
      'type'             => MENU_LOCAL_TASK,
      'context'          => MENU_CONTEXT_INLINE,
      'weight'           => 10,
      'file'             => 'entity_toolbox.entities.functions.inc',
      'file path'        => ENTITY_TOOLBOX_PATH,
    );
    $items[$this->entityType . '/' . $wildcard]             = array(
      'title callback'   => $title_callback,
      'title arguments'  => array(1),
      'page callback'    => $page_callback,
      'page arguments'   => array(1),
      'access callback'  => $access_callback,
      'access arguments' => array('view', 1),
      'type'             => MENU_CALLBACK,
    );
  }

}

/**
 * Class EntityToolboxNotFieldableUIController
 *
 * The default UI Controller for non fieldable entities.
 */
class EntityToolboxNotFieldableUIController extends EntityToolboxUIController {

  /**
   * Provides the menu items for hook_menu().
   *
   * @see hook_menu().
   */
  public function hook_menu() {
    $items                                                    = array();
    $id_count                                                 = $this->id_count;
    $label                                                    = $this->labelSingle();
    $label_plural                                             = $this->labelPlural();
    $create_callback                                          = $this->toolboxInfo['callbacks']['create'];
    $access_callback                                          = $this->toolboxInfo['callbacks']['access'];
    $page_callback                                            = $this->toolboxInfo['callbacks']['page'];
    $title_callback                                           = $this->toolboxInfo['callbacks']['title'];
    $wildcard                                                 = $this->wildcard();
    $items[$this->path]                                       = array(
      'title'            => $label_plural,
      'page callback'    => 'drupal_get_form',
      'page arguments'   => array(
        $this->entityType . '_overview_form',
        $this->entityType
      ),
      'description'      => 'Manage ' . $label_plural . ', including adding
		and removing fields and the display of fields.',
      'access callback'  => 'entity_access',
      'access arguments' => array('view', $this->entityType),
      'file'             => 'includes/entity.ui.inc',
    );
    $items[$this->path . '/add']                              = array(
      'title'            => "Add a $label",
      'page callback'    => 'entity_toolbox_ui_edit_form',
      'page arguments'   => array(entity_create($this->entityType, array())),
      'access callback'  => $access_callback,
      'access arguments' => array('create', $this->entityType),
      'type'             => MENU_LOCAL_ACTION,
      'weight'           => 20,
      'file'             => 'entity_toolbox.entities.functions.inc',
      'file path'        => ENTITY_TOOLBOX_PATH,
    );
    $items[$this->path . '/manage/%entity_object']            = array(
      'title'            => 'Edit',
      'title callback'   => 'entity_label',
      'title arguments'  => array($this->entityType, $id_count + 1),
      'page callback'    => 'entity_toolbox_ui_edit_form',
      'page arguments'   => array($id_count + 1, $this->entityType),
      'load arguments'   => array($this->entityType),
      'access callback'  => $access_callback,
      'access arguments' => array('update', $this->entityType, $id_count + 1),
      'file'             => 'entity_toolbox.entities.functions.inc',
      'file path'        => ENTITY_TOOLBOX_PATH,
    );
    $items[$this->path . '/manage/%entity_object/edit']       = array(
      'title'          => 'Edit',
      'load arguments' => array($this->entityType),
      'type'           => MENU_DEFAULT_LOCAL_TASK,
    );
    $items[$this->path . '/manage/%entity_object' . '/clone'] = array(
      'title'            => 'Clone',
      'page callback'    => 'entity_toolbox_ui_clone_form',
      'page arguments'   => array($id_count + 1, $this->entityType),
      'load arguments'   => array($this->entityType),
      'access callback'  => $access_callback,
      'access arguments' => array('create', $this->entityType),
    );
    $items[$this->path . '/manage/%entity_object' . '/%']     = array(
      'page callback'    => 'drupal_get_form',
      'page arguments'   => array(
        $this->entityType . '_operation_form',
        $this->entityType,
        $id_count + 1,
        $id_count + 2
      ),
      'load arguments'   => array($this->entityType),
      'access callback'  => $access_callback,
      'access arguments' => array('delete', $this->entityType, $id_count + 1),
      'file'             => 'includes/entity.ui.inc',
    );

    if (!empty($this->entityInfo['exportable']) && $this->entityInfo) {
      $items[$this->path . '/import'] = array(
        'title callback'   => 'entity_ui_get_action_title',
        'title arguments'  => array('import', $this->entityType),
        'page callback'    => 'drupal_get_form',
        'page arguments'   => array(
          $this->entityType . '_operation_form',
          $this->entityType,
          NULL,
          'import'
        ),
        'access callback'  => $access_callback,
        'access arguments' => array('create', $this->entityType),
        'file'             => 'includes/entity.ui.inc',
        'type'             => MENU_LOCAL_ACTION,
      );
    }

  }
}