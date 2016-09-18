<?php

require_once 'EntityToolboxInfoBuilder.inc';
require_once ENTITY_TOOLBOX_PATH . '/src/classes/models/hooks/entity_toolbox_info/EntityToolboxInfoModel.inc';


/**
 * Class EntityToolboxInfoBuilder
 *
 * Base build class for hook_entity_toolbox_info().
 */
class EntityToolboxInfoBuilderFieldable extends EntityToolboxInfoBuilder {

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'model_class'          => 'EntityToolboxInfoModelFieldable',
      'key_builders_classes' => array(
        'classes'    => 'EntityToolboxInfoClassesBuilderFieldable',
        'properties' => 'EntityToolboxInfoPropertiesBuilderFieldable',
        'operations' => 'EntityToolboxInfoOperationsBuilderFieldable',
      )
    ), $args);
    parent::__construct($args);
  }
}