<?php

/**
 * Class ContribHookValueBuilder
 */
class ContribHookValueBuilder extends HookValueBuilder {
  /**
   * @var array $toolboxInfo
   *   The toolbox info for the entity_type.
   */
  protected $toolboxInfo = array();

  /** {{@inheritdoc}} */
  public function __construct($hook, $entityType, array $args = array()) {
    parent::__construct($hook, $entityType, $args);
    $this->toolboxInfo = entity_toolbox_get_info($this->entityType);
    $this->setTemplateVars($this->extractToolboxInfoTemplateVars());
  }

  protected function extractToolboxInfoTemplateVars() {
    return array(
      'entity_type'      => $this->entityType,
      'fieldable'        => $this->toolboxInfo['fieldable'],
      'label'            => $this->toolboxInfo['labels']['single'],
      'label_plural'     => $this->toolboxInfo['labels']['plural'],
      'entity_class'     => $this->toolboxInfo['classes']['entity']['class'],
      'controller_class' => $this->toolboxInfo['classes']['controller']['class'],
      'module'           => $this->toolboxInfo['module'],
      'label_callback'   => $this->toolboxInfo['callbacks']['label'],
      'create_callback'  => $this->toolboxInfo['callbacks']['create'],
      'access_callback'  => $this->toolboxInfo['callbacks']['access'],
      'uri_callback'     => $this->toolboxInfo['callbacks']['uri'],
      'root_path'        => $this->toolboxInfo['root path'],
    );
  }

  protected function extractToolboxInfoPropertyTemplateVars($propertyName) {
    $propertyInfo = $this->toolboxInfo['properties'][$propertyName];
    $vars         = array(
      'property_label'            => $propertyInfo['label'],
      'property_description'      => $propertyInfo['description'],
      'property_drupal_type'      => $propertyInfo['drupal type'],
      'property_required'         => $propertyInfo['required'],
      'property_has_translations' => $propertyInfo['has_translations'],
      'property_has_revisions'    => $propertyInfo['has_revisions'],
      'property_views_expose'     => $propertyInfo['views expose'],
    );
    foreach ($propertyInfo['callbacks'] as $callbackType => $callback) {
      $vars['property_' . $callbackType . '_callback'] = $callback;
    }

    return $vars;
  }
}