<?php

/**
 * Class EntityInfoBuilder
 *
 * Base build class for hook_entity_info().
 */
class EntityInfoBuilder extends EntityToolboxDependentHookBuilder {
  /**
   * @var bool $fieldable
   *   If the entity_type is fieldable or not.
   */
  protected $fieldable;

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'hook'                 => 'entity_info',
      'key_builders_classes' => array(
        'admin ui' => 'AdminUIBuilder',
      )
    ), $args);
    parent::__construct($args);
  }

  protected function initTemplateVars() {
    $this->templateVars += $this->extractToolboxInfoTemplateVars();
  }

  protected function buildAdminUi() {
    return $this->getKeyBuilder('admin ui')->build();
  }

  protected function buildEntityKeys() {
    return $this->toolboxInfo['keys'];
  }

  protected function buildInlineEntityForm() {

  }
}